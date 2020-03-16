/*   gui.cpp
DATE Jan 16 2020
AUTH Zach Grow
DESC Contains definitions of the GameGUI class, which displays the game
     interface, including menu drawing and selection
*/

#include "BearLibTerminal.h"
#include "map.hpp"
#include "player.hpp"
#include "gui.hpp"
#include "obstacle.hpp"
#include <iostream>
#include <string>
//#include <list>

using namespace std;
GameGUI::MessageLog GameGUI::globalMsgLog;
vector<string> GameGUI::MessageLog::messageList;
// **** GameGUI Methods
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

LAYER MODEL
NOTE: clear_area() affects CURRENT layer, clear() affects ALL layers!
NOTE: Only layer 0 has a background color! All other layers have transp. bkgrnd
255
...
09	GUI Elements
08	SFX
07	SFX
06	SFX
05	Actor (Upper)
04	Actor (Middle)
03	Actor (Lower)
02	Map Terrain
01	(Reserved)
00	BACKGROUND - Reserved

Each panel within the GUi will have its dimensions calculated when the game is loaded.
This class will define some sane minimums in case the defined/calculated values are wrongly-sized.
*/
GameGUI::GameGUI() :
statPanelWidthMinimum(36),
msgPanelWidthMinimum(40),
msgPanelHeightMinimum(10)
{	// default constructor

}
GameGUI::~GameGUI() {
	// default destructor

}
void GameGUI::initialize(uint maxWidth, uint maxHeight, Player *playerPtr, GameMap *mapPtr, list<Obstacle*> *obstacles, list<Vendor*> *vendors) {
	// Sets up a created GameGUI object to the runtime default configuration
	// Obtain pointers to the game objects we want to display
	playerObject = playerPtr;
	mapObject = mapPtr;
	obstacleList = obstacles;
	vendorList = vendors;
//	clog << "Link to player object at: " << playerPtr << endl;
	// Assign the maximum parameters
	windowWidth = maxWidth;
	windowHeight = maxHeight;
	// Calculate the dimensions of the map display
	mapViewportWidth = ((windowWidth - statPanelWidthMinimum - 3) < msgPanelWidthMinimum ? msgPanelWidthMinimum : (windowWidth - statPanelWidthMinimum - 3));
	mapViewportHeight = (windowHeight - msgPanelHeightMinimum - 3);
	// Create the individual panel objects
	mapDisplay.initialize(1, 1, mapViewportWidth, mapViewportHeight);
	statPanel.initialize((windowWidth - statPanelWidthMinimum + 1), 1, statPanelWidthMinimum, (windowHeight - 2));
	messageDisplay.initialize(2, (windowHeight - msgPanelHeightMinimum), msgPanelWidthMinimum, msgPanelHeightMinimum);
}
void GameGUI::render() {
	// draws the interface onto the screen
	// -- can use terminal_crop to set scene/layer sizes?
	// -- need some helper funcs to wrap around BLT's print funcs
	// -- need some line-drawing methods
	terminal_bkcolor("black"); // Set the background color
	terminal_clear(); // Wipe everything off
	displayMap();
	displayMessageLog();
	displayStatPanel();
	drawGUIFrame();
	terminal_refresh(); // Tell BLT to go ahead and update the display
}
void GameGUI::addMessage(const string& message) {
	globalMsgLog.add(message);
}
/***	Box-Drawing Char Unicode Codepoints
		topLeft		= 0x250C,
		topRight	= 0x2510,
		bottomLeft	= 0x2514,
		bottomRight	= 0x2518,
		hLine		= 0x2500,
		vLine		= 0x2502,
		leftT		= 0x251C,
		rightT		= 0x2524,
		upperT		= 0x252C,
		lowerT		= 0x2534,
		cross		= 0x253C
		*/
void GameGUI::drawGUIFrame() {
	// Handles the line-drawing methods to paint the interface borders
	// METHOD
	// Draw the long lines that cross the screen
	uint xMaximum = windowWidth - 1;
	uint yMaximum = windowHeight - 1;
//	clog << "windowWidth: " << windowWidth << endl;
//	clog << "windowHeight: " << windowHeight << endl;
//	clog << "xMax: " << xMaximum << endl;
//	clog << "yMax: " << yMaximum << endl;
	terminal_bkcolor("black");
	terminal_color("dark grey");
	drawHorizontalLine(0, 0, windowWidth);
	drawHorizontalLine(0, (yMaximum - msgPanelHeightMinimum), (windowWidth - statPanelWidthMinimum));
	drawHorizontalLine(0, yMaximum, windowWidth);
	drawVerticalLine(0, 0, windowHeight);
	drawVerticalLine((xMaximum - statPanelWidthMinimum), 0, windowHeight);
	drawVerticalLine(xMaximum, 0, windowHeight);
	// Draw the corners of the boxes by putting chars at those locations
	// (see above diagram for the order in which the corners are drawn)
	uint innerXPosition= xMaximum - statPanelWidthMinimum;
	uint innerYPosition = yMaximum - msgPanelHeightMinimum;
	terminal_put(0, 0, 0x250C); // top left
	terminal_put(xMaximum, yMaximum, 0x2518); // bottom right
	terminal_put(xMaximum, 0, 0x2510); // bottom left
	terminal_put(0, yMaximum, 0x2514); // top right
	terminal_put(innerXPosition, 0, 0x252C); // #4
	terminal_put(0, innerYPosition, 0x251C); // #5
	terminal_put(innerXPosition, innerYPosition, 0x2524); // #6
	terminal_put(innerXPosition, yMaximum, 0x2534); // #7
}
void GameGUI::displayMap() {
	// Display the currently-explored map
	// Get the size of the map
	uint mapWidth = mapObject->getWidth();
	uint mapHeight = mapObject->getHeight();
//	clog << "Detected map dims: " << mapWidth << "x" << mapHeight << endl;
//	clog << "Map offsets: " << mapViewHorizontalOffset << "x" << mapViewVerticalOffset << endl;
	int mapViewHorizontalOffset = 0;
	int mapViewVerticalOffset = 0;
	if (mapWidth < mapViewportWidth) {
		mapViewHorizontalOffset = (mapViewportWidth - mapWidth) / 2;
	}
	if (mapHeight < mapViewportHeight) {
		mapViewVerticalOffset = (mapViewportHeight - mapHeight) / 2;
	}
	uint cursorXOrigin = mapViewHorizontalOffset + mapDisplay.xOrigin;
	uint cursorYOrigin = mapViewVerticalOffset + mapDisplay.yOrigin;
	// Display the map
	for (uint xIndex = 0; xIndex < mapWidth; xIndex++) {
		for (uint yIndex = 0; yIndex < mapHeight; yIndex++) {
			if (mapObject->getObserved(xIndex, yIndex)) { // Has the player seen this tile before?
				// Set the background first
				terminal_layer(0);
				uint tileColor = mapObject->getTileColorAt(xIndex,yIndex);
				terminal_bkcolor((tileColor - 0x22000000)); // Use a slightly darker color for the bkground
				terminal_put(cursorXOrigin + xIndex, cursorYOrigin + yIndex, ' ');
				// Draw the terrain symbols
				terminal_layer(2); // Move to the terrain layer
				terminal_color(tileColor);
				terminal_put(cursorXOrigin + xIndex, cursorYOrigin + yIndex, mapObject->getTileSymbolAt(xIndex, yIndex));
			} else {
				terminal_layer(0);
				terminal_bkcolor("black");
				terminal_put(cursorXOrigin + xIndex, cursorYOrigin + yIndex, ' ');
				terminal_layer(2); // Move to the terrain layer
				terminal_color("black");
				terminal_put(cursorXOrigin + xIndex, cursorYOrigin + yIndex, ' ');
			}
		}
	}
	// Display the player's location within the map
	terminal_layer(5);
	terminal_color(playerObject->getColor()); // no way to obtain player color yet
	Pos actorPosn = playerObject->getPos();
	terminal_put(actorPosn.x + cursorXOrigin, actorPosn.y + cursorYOrigin, playerObject->getSymbol());
	// Display all of the game obstacles
	terminal_layer(4);
	if (!obstacleList->empty()) {
		for (auto obstIter = obstacleList->begin(); obstIter != obstacleList->end(); obstIter++) {
			if ((*obstIter)->isActive()) {
				terminal_color((*obstIter)->getColor());
				actorPosn = (*obstIter)->getPos();
				terminal_put(actorPosn.x + cursorXOrigin, actorPosn.y + cursorYOrigin, (*obstIter)->getSymbol());
			}
		}
	}
	if (!vendorList->empty()) {
		for (auto vendIter = vendorList->begin(); vendIter != vendorList->end(); vendIter++) {
			if ((*vendIter)->getVis()) {
				terminal_color((*vendIter)->getColor());
				actorPosn = (*vendIter)->getPos();
				terminal_put(actorPosn.x + cursorXOrigin, actorPosn.y + cursorYOrigin, (*vendIter)->getSymbol());
			}
		}
	}
}
void GameGUI::displayStatPanel() {
	// Displays the player's name, HP, and assorted other statistics
	// FIXME: update to use the individual panel dimensions
	int cursorXPosition = statPanel.xOrigin;
	int cursorYPosition = statPanel.yOrigin;
	terminal_bkcolor("black");
	// Name
	terminal_color("grey");
	terminal_print(cursorXPosition, cursorYPosition, "Name:");
	cursorXPosition += 16;
	terminal_color("white");
//	terminal_print(cursorXPosition, cursorYPosition, "GENERIC");
	terminal_print(cursorXPosition, cursorYPosition, (playerObject->getName()).c_str());
	cursorXPosition = statPanel.xOrigin;
	cursorYPosition++;
	// HP: Current / Maximum
	terminal_color("light yellow");
	terminal_print(cursorXPosition, cursorYPosition, "$$$$:");
	//FIXME: How to do inline realignment?
	cursorXPosition += 16;
	terminal_color("yellow");
	terminal_printf(cursorXPosition, cursorYPosition, "$ %d", playerObject->getMoney());
	cursorXPosition = statPanel.xOrigin;
	cursorYPosition++;
	// Energy: Current / Maximum
	terminal_color("light blue");
	terminal_print(cursorXPosition, cursorYPosition, "Energy:");
	cursorXPosition += 16;
	terminal_color("blue");
	terminal_printf(cursorXPosition, cursorYPosition, "E %d", playerObject->getEnergy());
	cursorXPosition = statPanel.xOrigin;
	cursorYPosition++;
	// Player's current location
	terminal_color("white");
	terminal_print(cursorXPosition, cursorYPosition, "Location:");
	cursorXPosition += 10;
	terminal_printf(cursorXPosition, cursorYPosition, "%d, %d", playerObject->getPos().x, playerObject->getPos().y);
	cursorXPosition = statPanel.xOrigin;
	cursorYPosition++;
	// Player's toolbelt
	terminal_printf(cursorXPosition, cursorYPosition, "Tools:");
	cursorXPosition += 2;
	cursorYPosition++;
	if (playerObject->getToolbelt()->empty()) {
		terminal_printf(cursorXPosition, cursorYPosition, "NO TOOLS");
	} else {
		for (auto toolIter = playerObject->getToolbelt()->begin(); toolIter != playerObject->getToolbelt()->end(); toolIter++) {
			terminal_printf(cursorXPosition, cursorYPosition, (*toolIter).c_str());
			cursorYPosition++;
		}
	}
	cursorXPosition = statPanel.xOrigin;
}
void GameGUI::displayMessageLog() {
	// Prints the message log onto the screen
	// Obtain the starting position and set some defaults
	int cursorXPosition = messageDisplay.xOrigin;
	int cursorYPosition = messageDisplay.yOrigin + msgPanelHeightMinimum - 2;
	terminal_color("white"); // Default text color, can be overridden inline
	// Display some example text for now
	if (globalMsgLog.size() > 0) {
		vector<string>::reverse_iterator msgLogIter = globalMsgLog.messageList.rbegin();
		for ( ; msgLogIter != globalMsgLog.messageList.rend(); msgLogIter++) {
			if (cursorYPosition > messageDisplay.yOrigin) {
				// don't print messages if we're out of room
				terminal_print(cursorXPosition, cursorYPosition--, (*msgLogIter).c_str());
			}
		}
	}
}
// **** Window Drawing Methods
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
	terminal_print(1, 1, "Press Q or Alt+F4 to exit.");
	terminal_refresh();
}
void GameGUI::testMessageLog() {
	// Test function for the message log
	string testMessage = "Log size: ";
	testMessage.append(to_string(globalMsgLog.size() + 1));
	testMessage.append("\n");
	globalMsgLog.add(testMessage);
//	globalMsgLog.add("Press Q or Alt+F4 to exit.");
//	globalMsgLog.add("Or don't, it's not my job to tell you what to do.");

}
// **** GUIPanel Methods
void GameGUI::GUIPanel::initialize(uint inputX, uint inputY, uint inputWidth, uint inputHeight) {
	xOrigin = inputX;
	yOrigin = inputY;
	width = inputWidth;
	height = inputHeight;
}
// **** MessageLog Methods
int GameGUI::MessageLog::add(const string& newMessage) {
	// Adds the input string to the message log list
	messageList.push_back(newMessage);
	return messageList.size();
}
