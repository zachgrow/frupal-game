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
CALLED BY GameEngine: (ie do not call them here!)
BLT CONFIGURATION
int  terminal_open(); // Starts BLT
int  terminal_set(configString); // Configures ALL non-default params of BLT
void terminal_close(); // Stops BLT

INPUT HANDLING
int  terminal_state(int slot); // Returns value of specified state slot:
int  terminal_check(int slot); // Wrapper for _state to assist with type matching
// FIXME: Include a list of state slots?
int  terminal_has_input(); // true if player input is waiting to be processed
int  terminal_read(); // (waits for and) returns next event from input queue
int  terminal_peek(); // returns value of next event on input queue (0 if empty)
color_t terminal_read_str( ... ); // displays user input onscreen (?)

CALLED BY GameGUI:
OUTPUT METHODS
void terminal_clear(); // Clears ALL LAYERS and sets bkcolor of all cells to current color
void terminal_clear_area(int x, int y, int w, int h); // As above, for selection
void terminal_crop(x, y, w, h); // sets a crop area of the current layer (?)
void terminal_refresh(); // Tell BLT to push all layers onto the screen
int  terminal_pick(x, y, int index); // Returns the char code of the specified tile
// NOTE: "index" specifies an index of a tile in the cell
// If no such tile exists in that cell, or the cell is empty, _pick returns 0
// To enumerate all tiles in a cell, incr. index until 0 is returned
color_t terminal_pick_color(x, y, index); // Returns color at specified tile
color_t terminal_pick_bkcolor(x, y); // Returns background color of the cell
dimensions_t terminal_measure(const char* s);
dimensions_t terminal_measure_ext(w, h, s);
// Returns the size a string would have /if/ it were printed to the screen
// _measure_ext works analogous to _put_ext and _print_ext

void terminal_put(x, y, int code); // Put the assoc. char code to those coords
void terminal_put_ext(x, y, dx, dy, int code, color_t* corners);
// Complex version of _put that allows specifying a tile offset as well as
// allowing tile corners to be painted in different colors
// dx and dy specify the tile offset in pixels relative to tile's normal posn
// corners specifies an array of four color_t values in this order:
//		top-left, bottom-left, bottom-right, top-right
// The corners option can be used to smooth gradients and tile transitions
// if NULL is passed as corners param, current foreground color is used

dimensions_t terminal_print(x, y, const char* s);
dimensions_t terminal_print_ext(x, y, width, height, int align, const char* s);
// _print will print a string on the screen from the given coordinates, placed
// as if terminal_put was called (allowing use of standard options)
// _print_ext allows optional auto-wrapping (within its bounds) and alignment:
//	ALIGNMENT VALUES: (combinations allowed)
//	TK_ALIGN_DEFAULT (top left)
//	TK_ALIGN_LEFT
//	TK_ALIGN_RIGHT
//	TK_ALIGN_CENTER (horizontally)
//	TK_ALIGN_TOP
//	TK_ALIGN_BOTTOM
//	TK_ALIGN_CENTER (vertically)
// The string to be printed can be modified inline using [tags], ie:
//	terminal_print("[color=red]^[/color] (red goblin)", dx, dy);
//	TAGS:
//	Color: [color=NAME] (will be parsed by _color_from_name)
//	Arbitrary character codes: [U+E001] or [0xE001], etc
//	Symbol combination: "a[+]^" produces an "a" with a caret accent
//	Pixel offset: [offset=x,y] adds offset to all chars as if by _put_ext
//	Font change: [font=somename]
// All tags can be closed with a symmetrical tag, ie [color] xxx [/color]
// Tag closure is unneccesary, and tag nesting is technically accidental:
// each tag invokes its own call to a set/reset function (NOT LIKE HTML)
// Note that _print and _measure support all flavors of printf, wprint, etc

OUTPUT STATE
void terminal_color(color_t color); // Sets foreground color by 00xAARRGGBB format
void terminal_bkcolor(color_t color); // Sets background color by 00xAARRGGBB format
void terminal_composition(int mode); // Sets character composition mode ON or OFF
void terminal_layer(int layer); // Sets the current layer to draw output upon (0 = lowest and default)

UTILITIES
void terminal_delay(int interval); // Suspend execution for time in milliseconds
color_t color_from_name(name); // returns numeric value of specified color
color_t color_from_argb(A, R, G, B); // as _from_name, but with ARGB values
*/
/* *** The GUI Model Diagram
  |<-     w          ->|       POINT  COORDS
- 0------ ... -4- ... -2         0     0, 0
^ |(0,0)       |       |         1     i, j
| |   MAP      | S     |         2     i, 0
h |            |  T    |         3     0, j
| 5--    ...  -6   A   |         4     (i-18), 0
v |  MESSAGES  |    T  |         5     0, (j-10)
- 3-          -7-     -1         6     ([4].x), ([5].y)
                        (i, j)   7     ([4].x), j
BOUNDING LIMITS
The map's minimum size is 20x20
The viewport's minimum size is 40x20 (to allow 40 width for message output)
The stat panel's minimum width is 18
The terminal window's minimum size is 60x42
The maximum width and height are supplied by GameEngine on GUI creation
*/
GameGUI::GameGUI() {
	// default constructor
	// Need to decide on some default terminal dimensions?

}
GameGUI::GameGUI(unsigned int maxWidth, unsigned int maxHeight) :
screenWidth(maxWidth),
screenHeight(maxHeight),
statPanelWidth(36),
messagePanelHeight(10)
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
	// polls game state to see if any of the GUI elements need to change
	// performs scene composition

}
void GameGUI::render() {
	// draws the interface onto the screen
	// -- can use terminal_crop to set scene/layer sizes?
	// -- need some helper funcs to wrap around BLT's print funcs
	// -- need some line-drawing methods
	drawGUIBoxes();
	// drawMapView
	// writeMessageLog
	// drawStatPanel
	testBLT();
	terminal_refresh(); // Tell BLT to go ahead and update the display
}
void GameGUI::drawGUIBoxes() {
	// Handles the line-drawing methods to paint the interface borders
	// METHOD
	// Draw the long lines that cross the screen
	unsigned int xMaximum = screenWidth - 1;
	unsigned int yMaximum = screenHeight - 1;
	clog << "screenWidth: " << screenWidth << endl;
	clog << "screenHeight: " << screenHeight << endl;
	clog << "xMax: " << xMaximum << endl;
	clog << "yMax: " << yMaximum << endl;
	drawHorizontalLine(0, 0, screenWidth);
	drawHorizontalLine(0, (yMaximum - messagePanelHeight), (screenWidth - statPanelWidth));
	drawHorizontalLine(0, yMaximum, screenWidth);
	drawVerticalLine(0, 0, screenHeight);
	drawVerticalLine((xMaximum - statPanelWidth), 0, screenHeight);
	drawVerticalLine(xMaximum, 0, screenHeight);
	// Draw the corners of the boxes by putting chars at those locations
	// (see above diagram for the order in which the corners are drawn)
	unsigned int innerXPosition= xMaximum - statPanelWidth;
	unsigned int innerYPosition = yMaximum - messagePanelHeight;
	terminal_put(0, 0, 0x250C); // top left
	terminal_put(xMaximum, yMaximum, 0x2518); // bottom right
	terminal_put(xMaximum, 0, 0x2510); // bottom left
	terminal_put(0, yMaximum, 0x2514); // top right
	terminal_put(innerXPosition, 0, 0x252C); // #4
	terminal_put(0, innerYPosition, 0x251C); // #5
	terminal_put(innerXPosition, innerYPosition, 0x2524); // #6
	terminal_put(innerXPosition, yMaximum, 0x2534); // #7
}
void GameGUI::drawHorizontalLine(unsigned int x, unsigned int y, int length) {
	// Draws a horizontal line from the specified point
	// Specifying a negative length will draw the line 'backwards'
	// If length == 0, it will fall through and do nothing
	if (length > 0) {
		for (int offset = 0; offset < length; offset++) {
			terminal_put((x + offset), y, 0x2500);
		}
	} else if (length < 0) {
		for (int offset = 0; offset < length; offset--) {
			terminal_put((x + offset), y, 0x2500);
		}
	}
}
void GameGUI::drawVerticalLine(unsigned int x, unsigned int y, int length) {
	// Draws a vertical line from the specified point
	// Specifying a negative length will draw the line 'backwards'
	// If length == 0, it will fall through and do nothing
	if (length > 0) {
		for (int offset = 0; offset < length; offset++) {
			terminal_put(x, (y + offset), 0x2502);
		}
	} else if (length < 0) {
		for (int offset = 0; offset < length; offset--) {
			terminal_put(x, (y + offset), 0x2502);
		}
	}
}
void GameGUI::testBLT() {
	// Debugging function to assist with checking BearLibTerminal functions
	// try printing something to the screen and wait until the window is closed
	terminal_print(1, 1, "Hello, world!");
	terminal_refresh();
	while (terminal_read() != TK_CLOSE);
}
