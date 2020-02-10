/*   engine.hpp
DATE Jan 16 2020
AUTH Josiah Baldwin, Zach Grow
DESC Contains definitions of the GameEngine class
*/
#ifndef FRUPALGAME_SRC_ENGINE_HPP_INCLUDED
#define FRUPALGAME_SRC_ENGINE_HPP_INCLUDED

#include "map.hpp"
#include "player.hpp"
#include "gui.hpp"
#include <string>		// String object for text
#include <random>

struct GameEngine
{
	enum directions {
		UP,
		LEFT,
		RIGHT,
		DOWN
	};

	enum GameState {
		STARTUP,
		RUNNING,
		VICTORY,
		DEFEAT,
		ERROR,
	} gameState;
	bool debug_mode;

	unsigned int screenWidth; // Width of terminal in # of monospace chars
	unsigned int screenHeight; // Height of terminal in # of monospace chars
	int jewelsX;
	int jewelsY;
	GameMap worldMap;
	std::vector<int> tile_energy_costs_;
	Player player;
	GameGUI gui;
	std::string terminalFontPath; // Contains relative path to the terminal font
	unsigned int terminalFontSize; // Size of the terminal font
	static int getRandomValue(int minimum, int maximum);
	static std::mt19937 randomEng;

	GameEngine(int health, int money, bool debug_mode) noexcept;	// Default constructor
	void loop();			// Core game loop
	bool initialize(const std::string& configFile); // Initialize the engine's components
	void terminate();		// Performs end-of-game cleanup before the engine itself is to be shutdown
	bool loadConfiguration(const std::string& configFile); // Loads external config
	std::string generateBLTConfigString(); // Generates a BearLibTerminal configuration string for terminal_set()

	void move_direction(directions dir);
};

#endif // FRUPALGAME_SRC_ENGINE_HPP_INCLUDED
