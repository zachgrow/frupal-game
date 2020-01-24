/*   gui.hpp
DATE Jan 16 2020
AUTH Zach Grow
DESC Implements the GameGUI class, which handles the system input/output and the
     interface, including menu drawing and selection
*/
#ifndef FRUPALGAME_SRC_GUI_HPP_INCLUDED
#define FRUPALGAME_SRC_GUI_HPP_INCLUDED

#include "tile.hpp"
#include <string>
#include <vector>

class GameGUI {
	public:
		GameGUI();
		GameGUI(unsigned int maxWidth, unsigned int maxHeight);
		~GameGUI();
		void initialize(); // Initializes a GameGUI to initial parameters
		void update(); // Polls the game state for changes in displayed info
		void render(); // Draws the interface onto the screen
		void testBLT(); // BearLibTerminal debugging/test function
	
	private:
		void drawGUIBoxes();
		void drawHorizontalLine(unsigned int x, unsigned int y, int length);
		void drawVerticalLine(unsigned int x, unsigned int y, int length);
		struct Message {
			std::string messageText;
			// text color?
			Message(const std::string *inputText);
			~Message();
		};
/*		BoxChar	:	  int { // Lightweight (default)
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
		
		unsigned int screenWidth;
		unsigned int screenHeight;
		std::string fontPath;
		// need a list of Messages for the message log
		unsigned int statPanelWidth;
		unsigned int messagePanelHeight;
};

#endif // FRUPALGAME_SRC_GUI_HPP_INCLUDED
