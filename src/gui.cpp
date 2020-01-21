/*   gui.hpp
DATE Jan 16 2020
AUTH Zach Grow
DESC Contains definitions of the GameGUI class, which displays the game
     interface, including menu drawing and selection
*/

#include "BearLibTerminal.h"
#include "gui.hpp"
#include <iostream>
#include <string>

using namespace std;

/* *** A short guide to BearLibTerminal API - Jan 19 2020 (Zach)
int  terminal_open(); // Inits BLT instance with default params (MUST CALL 1st)
void terminal_close(); // Closes BLT instance
int  terminal_set(const char* configString): // Sets up an instance using the given configString
void terminal_color(color_t color); // Sets foreground color by 00xAARRGGBB format
void terminal_bkcolor(color_t color); // Sets background color by 00xAARRGGBB format

*/

GameGUI::GameGUI() {
	// default constructor
	// Need to decide on some default terminal dimensions?

}
GameGUI::GameGUI(unsigned int maxWidth, unsigned int maxHeight, string fullFontPath) :
screenWidth(maxWidth),
screenHeight(maxHeight),
fontPath(fullFontPath) {
	// Constructor with dimensions of terminal window
	// FIXME: Need some kind of guarantee on the sanity of the maxFOO params...
	if (!terminal_open()) { // Try creating a BearLibTerminal instance
		// If it didn't work, send an error message to stderr
		cerr << "*** GUI: There was a problem starting BearLibTerminal." << endl;
	}
	if (fullFontPath != "") {
		fontPath = fullFontPath;
	}
}
GameGUI::~GameGUI() {
	// default destructor
	terminal_close(); // Halt the BearLibTerminal instance
}
void GameGUI::initialize() {
	// Sets a created GameGUI object to initial valid conditions
	// - set a character string to the needed BLT options
	// - call terminal_set with the option string
	string windowTitleOption="title='FRUPAL'";
	string windowSizeOption="size=";
	windowSizeOption.append(to_string(screenWidth));
	windowSizeOption.append("x");
	windowSizeOption.append(to_string(screenHeight));
	// If we want to set up mouse input, it needs to be enabled here
	// If we want to specify custom color names, we can do that here too
	string fullOptionString; // Will contain the constructed option list // The terminal window title and dimensions will be explicitly set
	fullOptionString.append("window: ");
	fullOptionString.append(windowTitleOption);
	fullOptionString.append(", ");
	fullOptionString.append(windowSizeOption);
	// Only add the font option if it has been specified
	if (fontPath != "") {
		fullOptionString.append("; font: ");
		fullOptionString.append(fontPath);
	}
	fullOptionString.append(";"); // Terminating character
//	terminal_set(fullOptionString.c_str()); // Set up the BLT instance
}
void GameGUI::update() {
	// polls game state for changes in displayed information

}
void GameGUI::render() {
	// draws the interface onto the screen
	terminal_refresh(); // Tell BLT to go ahead and update the display
}
void GameGUI::testBLT() {
	// Debugging function to assist with checking BearLibTerminal functions
	// try printing something to the screen and wait until the window is closed
	terminal_print(1, 1, "Hello, world!");
	terminal_refresh();
	while (terminal_read() != TK_CLOSE);
}
