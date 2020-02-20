
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

static bool isValidDirection(int x, int y, Player* player, GameMap* map)
{
	// TODO Make checking.
	return true;
}

static void testAndSet(int direction, Player* player, GameMap* map)
{
	switch (direction) {
		case UP:
			break;
		case LEFT:
			break;
		case RIGHT:
			break;
		case DOWN:
			break;
		default:
			std::cerr << "Invalid argument passed to " << __func__ << "\n";
			break;
	}
}

void InputParser::checkAndParseInput(int key_stroke)
{
	switch (key_stroke) {
		case TK_UP:
		case TK_W:
			testAndSet(UP, player_, game_map_);
			break;
		case TK_LEFT:
		case TK_A:
			testAndSet(LEFT, player_, game_map_);
			break;
		case TK_RIGHT:
		case TK_D:
			testAndSet(RIGHT, player_, game_map_);
			break;
		case TK_DOWN:
		case TK_S:
			testAndSet(DOWN, player_, game_map_);
			break;
		default: break;
	}
}
