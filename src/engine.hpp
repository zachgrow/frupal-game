/*   engine.cpp
DATE Jan 16 2020
AUTH Josiah Baldwin, Zach Grow
DESC Contains definitions of the GameEngine class
*/
#ifndef FRUPALGAME_SRC_ENGINE_HPP_INCLUDED
#define FRUPALGAME_SRC_ENGINE_HPP_INCLUDED

#include "gui.hpp"
#include "tile.hpp"
#include <string>		// String object for text
#include <vector>

struct GameEngine
{
	unsigned int screenWidth; // Width of terminal in # of monospace chars
	unsigned int screenHeight;// Height of terminal in # of monospace chars
	int jewelsX;
	int jewelsY;
	std::vector<std::vector<Tile>> map;
	Player player;
	GameGUI gui;			// Pointer to the game interface object

	GameEngine() noexcept;	// Default constructor
	void loop();			// Core game loop
	bool initialize(const std::string& configFile); // Initialize the engine's components
	bool loadConfiguration(const std::string& configFile); // Loads external config
};

#endif // FRUPALGAME_SRC_ENGINE_HPP_INCLUDED
