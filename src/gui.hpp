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
		// addMessage(string message); // Adds a string to the message log
	
	private:
		void drawGUIFrame();
		void displayMap();
		void displayStatPanel();
		void displayMessageLog();
		void drawHorizontalLine(unsigned int x, unsigned int y, int length);
		void drawVerticalLine(unsigned int x, unsigned int y, int length);
		struct Message {
			std::string messageText;
			// text color?
			Message(const std::string *inputText);
			~Message();
		};
		
		unsigned int screenWidth;
		unsigned int screenHeight;
		std::string fontPath;
		// need a list of Messages for the message log
		unsigned int statPanelWidth;
		unsigned int messagePanelHeight;
};

#endif // FRUPALGAME_SRC_GUI_HPP_INCLUDED
