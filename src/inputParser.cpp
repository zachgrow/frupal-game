
#include "inputParser.hpp"
#include "player.hpp"
#include "map.hpp"
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

static int isValidDirection(int x, int y, Player* player, GameMap* map)
{
	if (x < 0 || y < 0 || x < map->getWidth() || y < map->getHeight())
		return false;
	return true;
}

static void testAndSet(int direction, Player* player, GameMap* map)
{
	auto pos = player->getPos();
	int x, y;
	switch (direction) {
		case UP:
			x = pos.x;
			y = pos.y - 1;
			if (isValidDirection(x, y, player, map))
				player->move("west");
			break;
		case LEFT:
			x = pos.x - 1;
			y = pos.y;
			if (isValidDirection(x, y, player, map))
				player->move("north");
			break;
		case RIGHT:
			x = pos.x + 1;
			y = pos.y;
			if (isValidDirection(x, y, player, map))
				player->move("south");
			break;
		case DOWN:
			x = pos.x;
			y = pos.y + 1;
			if (isValidDirection(x, y, player, map))
				player->move("east");
			break;
		default:
			std::cerr << "Invalid argument passed to " << __func__ << "\n";
			break;
	}

	player->setEnergy(player->getEnergy() - map->getTerrainCostAt(x, y));
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

