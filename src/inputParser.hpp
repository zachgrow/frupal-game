
#ifndef FRUPALGAME_SRC_INPUTPARSER_HPP_INCLUDED
#define FRUPALGAME_SRC_INPUTPARSER_HPP_INCLUDED

class Player;
class GameMap;

class InputParser {
	Player* player_;
	GameMap* game_map_;
	int previous_value_;
public:

	InputParser() = delete;

	InputParser(Player& player, GameMap& map);

	bool checkAndParseInput(int key_stroke);
};

#endif // FRUPALGAME_SRC_INPUTPARSER_HPP_INCLUDED
