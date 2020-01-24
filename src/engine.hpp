/*   engine.cpp
DATE Jan 16 2020
AUTH Josiah Baldwin, Zach Grow
DESC Contains definitions of the GameEngine class
*/
#ifndef FRUPALGAME_SRC_ENGINE_HPP_INCLUDED
#define FRUPALGAME_SRC_ENGINE_HPP_INCLUDED

#include "gui.hpp"
#include "player.hpp"
#include "tile.hpp"
#include <string>		// String object for text
#include <random>
#include <vector>

struct GameEngine
{
	enum GameState {
		STARTUP,
		RUNNING,
		VICTORY,
		DEFEAT,
		ERROR,
	} gameState;

	unsigned int screenWidth; // Width of terminal in # of monospace chars
	unsigned int screenHeight; // Height of terminal in # of monospace chars
	int jewelsX;
	int jewelsY;
//	std::vector<std::vector<Tile>> map;
	Player player;
	GameGUI gui;			// Pointer to the game interface object
	std::string terminalFontPath; // Contains relative path to the terminal font
	unsigned int terminalFontSize; // Size of the terminal font
	std::mt19937 randomEng;

	GameEngine() noexcept;	// Default constructor
	void loop();			// Core game loop
	bool initialize(const std::string& configFile); // Initialize the engine's components
	void terminate();		// Performs end-of-game cleanup before the engine itself is to be shutdown
	bool loadConfiguration(const std::string& configFile); // Loads external config
	std::string generateBLTConfigString(); // Generates a BearLibTerminal configuration string for terminal_set()
};

#endif // FRUPALGAME_SRC_ENGINE_HPP_INCLUDED