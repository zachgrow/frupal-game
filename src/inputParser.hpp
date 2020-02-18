
#ifndef FRUPALGAME_SRC_INPUTPARSER_HPP_INCLUDED
#define FRUPALGAME_SRC_INPUTPARSER_HPP_INCLUDED

class Player;

class InputParser {
	Player* player_;
	int previous_value_;
public:

	InputParser() = delete;

	InputParser(Player& player);

	void checkAndParseInput(int key_stroke);
};

#endif // FRUPALGAME_SRC_INPUTPARSER_HPP_INCLUDED
