/*   gui.hpp
DATE Jan 16 2020
AUTH Zach Grow
DESC Contains definitions of the GameGUI class, which displays the game
     interface, including menu drawing and selection
*/

#include <string>

class GameGUI {
	public:
		GameGUI();
		GameGUI(unsigned int maxWidth, unsigned int maxHeight, std::string fullFontPath);
		~GameGUI();
		void initialize(); // Initializes a GameGUI to initial parameters
		void update(); // Polls the game state for changes in displayed info
		void render(); // Draws the interface onto the screen
		void testBLT(); // BearLibTerminal debugging/test function
	
	private:
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
};
