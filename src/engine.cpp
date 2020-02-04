/*   engine.cpp
DATE Jan 16 2020
AUTH Josiah Baldwin, Zach Grow
DESC Contains implementation of game engine as well as main()
*/

#include "BearLibTerminal.h"
#include "gui.hpp"
#include "tile.hpp"
#include "player.hpp"
#include "engine.hpp"
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>		// Provides access to stdin/stdout (cout, cerr, etc)
#include <sstream>		// Object for conversion from std::string to input stream
#include <fstream>		// Simple file input/output

#define MAP_DIM 50
#define HELP_INFO "Pass --help for help\n" \
				  "     --DEBUG_MODE to log actions, (disables scoring)\n" \
				  "      -H integer for health\n" \
				  "      -M integer for money\n"
#define LEFT  0
#define UP    1
#define RIGHT 2
#define DOWN  3

int main(int argc, char** argv)
{
	std::string configFilePath = "config.txt";
	int health = -1;
	int money = -1;
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
						std::cerr << "Unknown argument exiting.\n";
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
	std::cout << "Success! Width x height: " << engine.screenWidth << "x" << engine.screenHeight << "\n";
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
player(health, money, "")
{
	// The default constructor
	gui = GameGUI(screenHeight, screenWidth); // Create a GUI instance
	map.resize(MAP_DIM);
	for (auto& i : map)
		i.resize(MAP_DIM);
}

void GameEngine::loop()
{
	// BLT display explicitly requires an initial call to _refresh() prior to
	// displaying anything onscreen
	terminal_refresh();
	// TK_CLOSE == true when the terminal window is closed
	bool keep_going = true;
	while (terminal_peek() != TK_CLOSE && keep_going) { // _peek does not block if false (unlike _read)
		// Fetch player action
		if (terminal_has_input()) { // Is there control input waiting?
			// Perform action
			// Parse the command input by reading it from terminal_
			int inputKey = terminal_read();
			if (inputKey == TK_Q)
				break;


			switch (inputKey) {
#if 0
				case TK_Q:
					// Send end message
					keep_going = false;
					break;
#endif
				case TK_A:
				case TK_LEFT:
					move_to_tile(LEFT);
					break;
				case TK_W:
				case TK_UP:
					move_to_tile(UP);
					break;
				case TK_D:
				case TK_RIGHT:
					move_to_tile(RIGHT);
					break;
				case TK_S:
				case TK_DOWN:
					move_to_tile(DOWN);
					break;
				default: break;
			}
			auto pos = player.getPos();
			std::cout << pos.x << ' ' << pos.y << "\n";
		}
		// Write result
		gui.update();
		gui.render();
	};
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

	gui.initialize(); // Initialize the GUI's state
	std::string bltConfigString = generateBLTConfigString();
//	std::clog << "*** Generated BLT configuration:\n    " << bltConfigString << endl;
	terminal_set(bltConfigString.c_str()); // Get BLT set up to its default state

	if (!debug_mode) {
		std::random_device rd;
		randomEng.seed(rd());
	}

	gameState = RUNNING;

	return true;
}

void GameEngine::terminate()
{
	// Performs closing-of-the-game methods before the engine itself shuts down
	// If we wanted to save the game automatically, we could do so here
	terminal_close(); // Halt the BearLibTerminal instance
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

void GameEngine::move_to_tile(int direction)
{
	assert(direction >= LEFT && direction <= DOWN);

	// Check if valid tile
	// deduct energy int
	switch (direction) {
		case UP:
			player.move("north");
			break;
		case LEFT:
			player.move("west");
			break;
		case RIGHT:
			player.move("east");
			break;
		case DOWN:
			player.move("south");
			break;
		default:
			break;
	}
}
