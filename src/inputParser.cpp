
#include "inputParser.hpp"
#include "player.hpp"
#include <BearLibTerminal.h>

#define LEFT  0
#define UP    1
#define RIGHT 2	
#define DOWN  3

InputParser::InputParser(Player& player)
: previous_value_(0)
{
	player_ = &player;
}

void checkAndParseInput(int key_stroke)
{
}

