/*   engine.cpp
DATE Jan 16 2020
AUTH Josiah Baldwin, Zach Grow
DESC Contains implementation of game engine as well as main()
*/

#include "gui.hpp"
#include "tile.hpp"
#include "player.hpp"
#include "engine.hpp"
#include <iostream>		// Provides access to stdin/stdout (cout, cerr, etc)
#include <sstream>		// Object for conversion from std::string to input stream
#include <fstream>		// Simple file input/output

//#include <cstdio>
//#include <vector>

int main(int argc, char** argv)
{
	std::string configFilePath = "config.txt";
	if (argc >= 2) {
		// Parse the command line options
		// need to invent some command line options!
		std::cerr << "*** No command line options are available at this time." << std::endl;
		return 1; // Exit the program by throwing a generic error code
	}
	GameEngine engine;
	if (!engine.initialize(configFilePath)) { // Try initializing the engine
		// If it didn't work for some reason, say so and exit
		std::cerr << "*** There was a problem loading the configuration." << std::endl;
		std::cerr << "*** The game will now exit." << std::endl;
		return 5; // Exit the program and throw a (different) error code
	}
	std::cout << "Success! Width x height: " << engine.screenWidth << "x" << engine.screenHeight << std::endl;
}
GameEngine::GameEngine() noexcept
{

}
bool GameEngine::initialize(std::string configFile)
{
	// Sets up the initial game state; this is NOT in the constructor because
	// we want to keep track of whether an error has arisen from the GameEngine
	// class or some other sub-module of the system
	if (!loadConfiguration(configFile)) { // Try loading the config file
		// If it didn't work, do not continue!
		return false;
	}
	gui = new GameGUI(screenHeight, screenWidth);
	return true;
}
void GameEngine::loop()
{
	// Fetch player action
	// Perform action
	// Write result
}
bool GameEngine::loadConfiguration(std::string inputFile)
{
	std::ifstream config(inputFile); // Open the configuration file
	if (!config) { // Was the config file opened successfully?
		// If not, display an error and exit
		std::cerr << "*** The configuration file could not be opened." << std::endl;
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
		// Break the stream into a key and its value at the =
		getline(lineStream, configKey, '=');
		getline(lineStream, configValue);
		// Find the matching configuration property and set its value
		// FIXME: Include sanity checks on input values
		// FIXME: Set up some kind of value defaults if anything's not set
		if (!config.eof()) { // Prevent trying the EOF char as a config key
			if (configKey == "screenWidth") {
				screenWidth = std::stoul(configValue, nullptr, 0);
			} else if (configKey == "screenHeight") {
				screenHeight = std::stoul(configValue, nullptr, 0);
			} else { // No matching config key was found!
				std::cerr << "Configuration key " << configKey << " is not recognized by the game." << std::endl;
			}
		}
	}
	config.close();
	// close the file
	return true;
}
