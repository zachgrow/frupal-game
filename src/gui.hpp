/*   gui.hpp
DATE Jan 16 2020
AUTH Zach Grow
DESC Implements the GameGUI class, which handles the system input/output and the
     interface, including menu drawing and selection
*/
#ifndef FRUPALGAME_SRC_GUI_HPP_INCLUDED
#define FRUPALGAME_SRC_GUI_HPP_INCLUDED

#include "map.hpp"
#include "player.hpp"
#include <string>
#include <vector>


class GameGUI {
	private:
		struct MessageLog { // semantic wrapper around the message log object
			std::vector<std::string> messageList;
			int add(std::string newMessage); // Returns # of messages in log
			uint size() { return messageList.size(); }
			// probably need some kind of log culling function(s)
			// NOTE: the message log is structured as a STACK, ie LIFO
		};

	public:
		GameGUI();
		~GameGUI();
		// Initializes a GameGUI to initial state
		void initialize(unsigned int maxWidth, unsigned int maxHeight, Player* playerPtr, GameMap* mapPtr,Vendor* vendorPtr);
		void update(); // Polls the game state for changes in displayed info
		void render(); // Draws the interface onto the screen
		void testBLT(); // BearLibTerminal debugging/test function
		void testMessageLog();
		// addMessage(string message); // Adds a string to the message log
		MessageLog globalMsgLog;

	private:
		void drawGUIFrame();
		void displayMap();
		void displayStatPanel();
		void displayMessageLog();
		void drawHorizontalLine(uint x, unsigned int y, int length);
		void drawVerticalLine(uint x, unsigned int y, int length);
		struct GUIPanel {
			unsigned int xOrigin;
			unsigned int yOrigin;
			unsigned int width;
			unsigned int height;
			// background color?
			void initialize(unsigned int inputX, unsigned int inputY, unsigned int inputWidth, unsigned int inputHeight);
		} mapDisplay, statPanel, messageLog;

		// Pointers for data retrieval
		Player* playerObject;
		GameMap* mapObject;
		Vendor* vendorObject;
		// Internal geometry information
		unsigned int windowWidth;
		unsigned int windowHeight;
		unsigned int mapViewportWidth;
		unsigned int mapViewportHeight;
		unsigned int statPanelWidthMinimum;
		unsigned int msgPanelWidthMinimum;
		unsigned int msgPanelHeightMinimum;
		// need a list of Messages for the message log
};

#endif // FRUPALGAME_SRC_GUI_HPP_INCLUDED
