
#include "inputParser.hpp"
#include "player.hpp"
#include <BearLibTerminal.h>

InputParser::InputParser(Player& player)
: previous_value_(0)
{
	player_ = &player;
}

void checkAndParseInput(int key_stroke)
{
}

