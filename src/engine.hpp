/*   engine.cpp
DATE Jan 16 2020
AUTH Josiah Baldwin, Zach Grow
DESC Contains definitions of the GameEngine class
*/

#include <string>		// String object for text

struct GameEngine
{
	unsigned int screenWidth; // Width of terminal in # of monospace chars
	unsigned int screenHeight;// Height of terminal in # of monospace chars
	std::string terminalFontPath;// Contains relative path to the terminal font
	GameEngine() noexcept;	// Default constructor
	GameGUI *gui;			// Pointer to the game interface object

	void loop();			// Core game loop
	bool initialize(std::string configFile); // Initialize the engine's components
	bool loadConfiguration(std::string configFile); // Loads external config
	void terminate();		// Performs end-of-game cleanup before the engine itself is to be shutdown
};
