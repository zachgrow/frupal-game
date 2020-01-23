/*   gui.cpp
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
GameGUI::GameGUI(unsigned int maxWidth, unsigned int maxHeight) :
screenWidth(maxWidth),
screenHeight(maxHeight)
{
	// Specific constructor
}
GameGUI::~GameGUI() {
	// default destructor

}
void GameGUI::initialize() {
	// Sets a created GameGUI object to initial valid conditions

}
void GameGUI::update() {
	// polls game state for changes in displayed information

}
void GameGUI::render() {
	// draws the interface onto the screen
//	testBLT();
	terminal_refresh(); // Tell BLT to go ahead and update the display
}
void GameGUI::testBLT() {
	// Debugging function to assist with checking BearLibTerminal functions
	// try printing something to the screen and wait until the window is closed
	terminal_print(1, 1, "Hello, world!");
	terminal_refresh();
	while (terminal_read() != TK_CLOSE);
}
