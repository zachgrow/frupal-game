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

typedef unsigned int uint;

class GameGUI {
	public:
		GameGUI();
		~GameGUI();
		void initialize(uint maxWidth, uint maxHeight); // Initializes a GameGUI to initial parameters
		void update(); // Polls the game state for changes in displayed info
		void render(); // Draws the interface onto the screen
		void testBLT(); // BearLibTerminal debugging/test function
		// addMessage(string message); // Adds a string to the message log
	
	private:
		void drawGUIFrame();
		void displayMap();
		void displayStatPanel();
		void displayMessageLog();
		void drawHorizontalLine(uint x, uint y, int length);
		void drawVerticalLine(uint x, uint y, int length);
		struct GUIPanel {
			uint xOrigin;
			uint yOrigin;
			uint width;
			uint height;
			// background color?
			void initialize(uint inputX, uint inputY, uint inputWidth, uint inputHeight);
		} mapDisplay, statPanel, messageLog;
		struct Message {
			std::string messageText;
			// text color?
			Message(const std::string *inputText);
			~Message();
		};
		
		// would really prefer static pointers to data input sources...
		uint windowWidth;
		uint windowHeight;
		uint statPanelWidthMinimum;
		uint msgPanelWidthMinimum;
		uint msgPanelHeightMinimum;
		// need a list of Messages for the message log
};

#endif // FRUPALGAME_SRC_GUI_HPP_INCLUDED
