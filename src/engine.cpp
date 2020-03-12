/*   engine.cpp
DATE Jan 16 2020
AUTH Josiah Baldwin, Zach Grow
DESC Contains implementation of game engine as well as main()
*/

#include "BearLibTerminal.h"
#include "engine.hpp"
#include "map.hpp"
#include "death.hpp"
#include "start_msg.hpp"
#include <cstdlib>
#include <cstring>
#include <iostream>		// Provides access to stdin/stdout (cout, cerr, etc)
#include <sstream>		// Object for conversion from std::string to input stream
#include <fstream>		// Simple file input/output

#define MAP_DIM 30
#define HELP_INFO "Pass --help for help\n" \
				  "     --DEBUG_MODE to default random seed, (disables scoring)\n" \
				  "      -H integer for health\n" \
				  "      -M integer for money\n"

std::mt19937 GameEngine::randomEng (47);

int main(int argc, char** argv)
{
	std::string configFilePath = "config.txt";
	int health = 100;
	int money = 100;
	bool debug_mode = 0;
	if (argc >= 2) {
		argv++;
		while (*argv != nullptr) {
			if (std::strcmp(*argv, "--help") == 0) {
				std::cout << HELP_INFO;
				return EXIT_SUCCESS;
			}
			else if (std::strcmp(*argv, "--DEBUG_MODE") == 0) {
				debug_mode = true;
			}
			else if (**argv == '-') {
				switch ((*argv)[1]) {
					case 'H':
						if (std::string(*argv).size() == 2)
							(*argv)++;
						else
							argv++;
						health = atoi(*argv);
						break;
					case 'M':
						if (std::string(*argv).size() == 2)
							(*argv)++;
						else
							argv++;
						money = atoi(*argv);
						break;
					default:
						std::cerr << "Unknown argument; exiting.\n";
						return EXIT_FAILURE;
				}
			} else {
				configFilePath = argv[1];
			}
			argv++; // Move to next arg
		}
	}
	GameEngine engine(health, money, debug_mode);
	if (!engine.initialize(configFilePath)) { // Try initializing the engine
		// If it didn't work for some reason, say so and exit
		std::cerr << "*** There was a problem loading the configuration.\n";
		std::cerr << "*** The game will now exit.\n";
		return 5; // Exit the program and throw a (different) error code
	}
//	std::cout << "Success! Width x height: " << engine.screenWidth << "x" << engine.screenHeight << "\n";
	// Invoke the game loop
	engine.loop();
	// WHEN the player has closed the game:
	engine.terminate();
}

// GameEngine class implementation
GameEngine::GameEngine(int health, int money, bool debug_mode) noexcept :
gameState(STARTUP),
debug_mode(debug_mode),
screenWidth(80),
screenHeight(50),
player(health, money, ""),
inputParser(player, worldMap)
{
	// The default constructor
	gui = GameGUI(); // Create a GUI instance
	player.setPos(MAP_DIM/2, MAP_DIM/2); // Move the player onto the map
}

void GameEngine::loop()
{
	// BLT display explicitly requires an initial call to _refresh() prior to
	// displaying anything onscreen
	terminal_refresh();
	worldMap.updateMap(player.getPos(), player.getVis());
	gui.render();
	int inputKey = 0;
	// TK_CLOSE == true when the terminal window is closed
	while (terminal_peek() != TK_CLOSE) { // _peek does not block if false (unlike _read)
		if (gameState == DEFEAT || gameState == VICTORY) break;
		// Fetch player action
		if (terminal_has_input()) { // Is there control input waiting?
			// Perform action
			// Parse the command input by reading it from terminal_
			inputKey = terminal_read();

			// Check with input parser
			if (gameState != RUNNING) {
				if (inputKey == TK_Q)
					break;
			}
			else if (!inputParser.checkAndParseInput(inputKey))
				break;

			if (player.getJewels()) {
				// Reveal map
				for (auto i = 0U; i < worldMap.getWidth(); i++)
					for (auto j = 0U; j < worldMap.getHeight(); j++)
						worldMap.getTileAt(i,j)->setObserved();
				gameState = VICTORY;
			}

			if (player.getEnergy() <= 0) {
				auto pos = player.getPos();
				if (worldMap.getTile(pos.x, pos.y) == 3) {
					Death_event mud(true);
					mud.react_to_player();
				}
				else {
					Death_event normal(false);
					normal.react_to_player();
				}
				gameState = DEFEAT;
			}

			worldMap.updateMap(player.getPos(), player.getVis());
		}
		// Check the obstacle list to see if anything should trigger
		for (auto obstIter = obstacleList.begin(); obstIter != obstacleList.end(); obstIter++) {
			if ((*obstIter)->isActive()) (*obstIter)->action(player);
		}
		// Do the same for the vendor list
		for (auto vendIter = vendorList.begin(); vendIter != vendorList.end(); vendIter++) {
			if ((*vendIter)->getPos() == player.getPos() && (*vendIter)->getVis()){ 
				GameGUI::addMessage("The vendor waves you over.");
				GameGUI::addMessage("(Use the terminal to respond)");
				gui.render();
				(*vendIter)->action(player);
			}
		}
		// Write result
		gui.render();
	};
	if (inputKey != TK_Q) { // did the player trigger a QUIT intentionally?
		if (gameState == DEFEAT) {
			GameGUI::addMessage(" **** G A M E  O V E R ****");
		}
		if (gameState == VICTORY) {
			GameGUI::addMessage(" **** V I C T O R Y ****");
		}
		GameGUI::addMessage("(Press Q to quit the game.)");
		while (terminal_read() != TK_Q) {
			// do nothing but wait for the player to agree to quit
			gui.render();
		}
	}
}

bool GameEngine::initialize(const std::string& configFile)
{
	// Sets up the initial game state; this is NOT in the constructor because
	// we want to keep track of whether an error has arisen from the GameEngine
	// class or some other sub-module of the system
	if (!loadConfiguration(configFile)) { // Try loading the config file
		// If it didn't work, do not continue!
		return false;
	}

	if (!terminal_open()) { // Try creating a BearLibTerminal instance
		// If it didn't work, send an error message to stderr
		std::cerr << "*** GUI: There was a problem starting BearLibTerminal.\n";
		return false;
	}
//	The RNG is seeded as part of its instantiation call as a static obj
	if (!debug_mode) {
		std::random_device rd;
		randomEng.seed(rd());
	} else {
		randomEng.seed(47);
	}
	player.setSymbol('@');
	player.setColor(0xFFCC3300);
	worldMap.generateMap(MAP_DIM, MAP_DIM, getRandomValue);
	// Set the Event static variable for the player object
	Event::setPlayerPtr(&player);
	Event::setMsgLogPtr(gui.addMessage);
	// add some obstacles to the map
	addObstacles();
	// add some vendors as well
	addVendors();
	gui.initialize(screenWidth, screenHeight, &player, &worldMap, &obstacleList, &vendorList); // Initialize the GUI's state
	std::string bltConfigString = generateBLTConfigString();
//	std::clog << "*** Generated BLT configuration:\n    " << bltConfigString << endl;
	terminal_set(bltConfigString.c_str()); // Get BLT set up to its default state
	gui.addMessage("Press Q or Alt+F4 to quit.");

	// Report start message
	Start_msg start_msg;
	start_msg.react_to_player();

	gameState = RUNNING;

	return true;
}

void GameEngine::terminate()
{
	// Performs closing-of-the-game methods before the engine itself shuts down
	// If we wanted to save the game automatically, we could do so here
	terminal_close(); // Halt the BearLibTerminal instance
	for (auto obstIter = obstacleList.begin(); obstIter != obstacleList.end(); obstIter++) {
		delete *obstIter;
	}
	for (auto vendIter = vendorList.begin(); vendIter != vendorList.end(); vendIter++) {
		delete *vendIter;
	}
}

bool GameEngine::loadConfiguration(const std::string& inputFile)
{
	std::ifstream config(inputFile); // Open the configuration file
	if (!config) { // Was the config file opened successfully?
		// If not, display an error and exit
		std::cerr << "*** The configuration file could not be opened." << "\n";
		return false;
	}
	std::stringstream lineStream; // Allows parsing single lines by chars
	std::string configLine; // Contains a whole line
	std::string configKey; // Contains the configuration property to be set
	std::string configValue; // Contains the new value for the config property
	while (!config.eof()) { // Parse all lines in the config file
		getline(config, configLine); // Obtain a full line
		lineStream.clear(); // Make sure the stream is empty
		lineStream << configLine; // Put the config line into the stream
		// Break the stream into a key and its value at the '='
		getline(lineStream, configKey, '=');
		getline(lineStream, configValue);
		// Find the matching configuration property and set its value
		// FIXME: Include sanity checks on input values
		// FIXME: Set up some kind of value defaults if anything's not set
		if (configKey != "") { // Prevent trying blank lines (ie trailing lines)
			if (configKey == "screenWidth") {
				screenWidth = std::stoul(configValue, nullptr, 0);
			} else if (configKey == "screenHeight") {
				screenHeight = std::stoul(configValue, nullptr, 0);
			} else if (configKey == "font") {
				terminalFontPath = configValue;
			} else if (configKey == "fontSize") {
				terminalFontSize = std::stoul(configValue, nullptr, 0);
			} else if (configKey == "playerEnergy") {
				player.setEnergy(std::stoul(configValue, nullptr, 0));
			} else if (configKey == "playerMoney") {
				player.setMoney(std::stoul(configValue, nullptr, 0));
			} else { // No matching config key was found!
				std::cerr << "*** Configuration key " << configKey << " is not recognized by the game." << "\n";
			}
		}
	}
	config.close();
	return true;
}

std::string GameEngine::generateBLTConfigString()
{
	// Generates a valid BearLibTerminal configuration string from our config
	// Set the window title
	std::string windowTitleOption="title=\'FRUPAL\'";
	// Set the window dimensions
	std::string windowSizeOption="size=";
	windowSizeOption.append(to_string(screenWidth));
	windowSizeOption.append("x");
	windowSizeOption.append(to_string(screenHeight));
	// If we want to set up mouse input, it needs to be enabled here
	// If we want to specify custom color names, we can do that here too
	// ***
	// Finally, generate the string to be returned
	std::string fullOptionString;
	// The terminal window title and dimensions will always be set
	fullOptionString.append("window: ");
	fullOptionString.append(windowTitleOption);
	fullOptionString.append(", ");
	fullOptionString.append(windowSizeOption);
	// Only add the font option if it has been specified
	if (terminalFontPath != "") {
		// If we specify a font, we MUST also specify a size
		fullOptionString.append("; font: ");
		fullOptionString.append(terminalFontPath);
		fullOptionString.append(", size=");
		fullOptionString.append(to_string(terminalFontSize));
	}
	fullOptionString.append(";"); // Terminating character
	return fullOptionString;
}

int GameEngine::getRandomValue(int minimum, int maximum) {
	std::uniform_int_distribution<int> dist(minimum, maximum);
	return dist(randomEng);
}

void GameEngine::addObstacles() {
	// Simple method: choose some squares by picking random x, y values
	// If the chosen location is a water tile, keep trying for a valid tile
	// Certain event types are not allowed to appear too often:
	// 1 Magic Jewel (always)
	// 1 Binoculars
	// 3 Nap
	// 3 Dehydration
	// 3 Greedy Tiles
	// 3 Jackpots
	// FIXME: This DOES NOT prevent multiple obstacles on the same tile!
	uint obstacleCount = 12;
	uint obstacleType = 0; // RANGE: 1 - 9
	uint obstacleXPos = 0; // RANGE: 0 - mapWidth
	uint obstacleYPos = 0; // RANGE: 0 - mapHeight
	Obstacle *newObstacle = nullptr;
	for (uint index = 0; index < obstacleCount; index++) {
		// Pick a tile within the map that is not water
		do {
			obstacleXPos = getRandomValue(0, (worldMap.getWidth() - 1));
			obstacleYPos = getRandomValue(0, (worldMap.getHeight() - 1));
//			clog << "OBST #" << index << " trying " << obstacleXPos << ", " << obstacleYPos << ": " << worldMap.getTile(obstacleXPos, obstacleYPos) << endl;
		} while (worldMap.getTile(obstacleXPos, obstacleYPos) == 1);
		// Choose an obstacle to put at that spot
//		obstacleType = getRandomValue(1, 9);
		obstacleType = 1;
		switch(obstacleType) {
			case 1:
				newObstacle = new Thief(obstacleXPos, obstacleYPos);
				break;
			default:
				cerr << "Invalid obstacle type generated!\n";
				break;
		}
		obstacleList.push_back(newObstacle);
	}
}
void GameEngine::addVendors() {
	// Adds some vendors with the default tool list to the game map
	uint vendorCount = 3;
	uint vendorXPos = 0;
	uint vendorYPos = 0;
	Vendor *newVendor = nullptr;
	for (uint index = 0; index < vendorCount; index++) {
		// Look for an open tile
		do {
			vendorXPos = getRandomValue(0, (worldMap.getWidth() - 1));
			vendorYPos = getRandomValue(0, (worldMap.getHeight() - 1));
		} while (worldMap.getTile(vendorXPos, vendorYPos) != 0);
//		clog << "new vendor at " << vendorXPos << ", " << vendorYPos << endl;
		newVendor = new Vendor();
		newVendor->setSymbol('&');
		int vendorColor = 0x000011 * index;
		if (index < 5) vendorColor += 0x555555;
		newVendor->setColor(0xFF000000 + vendorColor);
		newVendor->setPos(vendorXPos, vendorYPos);
		vendorList.push_back(newVendor);
	}
}

