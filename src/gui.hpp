/*   gui.hpp
DATE Jan 16 2020
AUTH Zach Grow
DESC Contains definitions of the GameGUI class, which displays the game
     interface, including menu drawing and selection
*/
#ifndef FRUPALGAME_SRC_GUI_HPP_INCLUDED
#define FRUPALGAME_SRC_GUI_HPP_INCLUDED

#include <string>

class GameGUI {
	public:
		GameGUI();
		GameGUI(unsigned int maxWidth, unsigned int maxHeight);
		~GameGUI();
		void initialize(); // Initializes a GameGUI to initial parameters
		void update(); // Polls the game state for changes in displayed info
		void render(); // Draws the interface onto the screen
	
	private:
		struct Message {
			std::string messageText;
			// text color?
			Message(const std::string *inputText);
			~Message();
		};
		unsigned int screenHeight;
		unsigned int screenWidth;
		// need a list of Messages for the message log
};

#endif // FRUPALGAME_SRC_GUI_HPP_INCLUDED
