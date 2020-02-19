
#include "inputParser.hpp"
#include "player.hpp"
#include <iostream>
#include <BearLibTerminal.h>

#define LEFT  0
#define UP    1
#define RIGHT 2	
#define DOWN  3

InputParser::InputParser(Player& player, GameMap& map)
: previous_value_(0)
{
	player_   = &player;
	game_map_ = &map;
}

bool isValidDirection(int x, int y, Player* player)
{
}

static void testAndSet(int direction, Player* player)
{
	switch (direction) {
		case UP:
		case LEFT:
		case RIGHT:
		case DOWN:
		default:
			std::cerr << "Invalid argument passed to " << __func__ << "\n";
			break;
	}
}

void InputParser::checkAndParseInput(int key_stroke)
{
}

