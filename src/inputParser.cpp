
#include "inputParser.hpp"
#include "player.hpp"
#include "map.hpp"
#include <iostream>
#include <BearLibTerminal.h>

#define LEFT 0
#define UP 1
#define RIGHT 2
#define DOWN 3

InputParser::InputParser(Player &player, GameMap &map)
	: previous_value_(0)
{
	player_ = &player;
	game_map_ = &map;
}

static bool isEnoughEnergy(Player *player)
{
	if (player->getEnergy() <= 0)
		return false;
	else
		return true;
}
static bool isValidDirection(int x, int y, Player *player, GameMap *map, int &deduction)
{
	//cout<<map->getTile(x,y)<<endl;
	// Is the player attempting to move outside the literal map bounds?
	if (x < 0 || y < 0 || x >= (int)map->getWidth() || y >= (int)map->getHeight())
	{
		std::cerr << "Out of range(" << x << ',' << y << ")\n";
		deduction = 0;
		return false;
	}

	// Get the energy cost of the tile that the player will be moving into
	deduction = map->getTerrainCostAt(x, y);

	// If the player does not have a boat and the destination is water...
	if (!player->hasTool("boat") && map->getTileAt(x, y)->getTile() == 1)
		return false;

	// Otherwise, check to see if the destination is obstructed somehow
	return !map->isObstructed(x, y);
}

static void testAndSet(int direction, Player *player, GameMap *map)
{
	auto pos = player->getPos();
	int x, y;
	int energy_deduction;
	const char *direction_str[] = {
		"north",
		"west",
		"south",
		"east",
	};
	switch (direction)
	{
	case UP:
		x = pos.x;
		y = pos.y - 1;
		break;
	case LEFT:
		x = pos.x - 1;
		y = pos.y;
		break;
	case RIGHT:
		x = pos.x + 1;
		y = pos.y;
		break;
	case DOWN:
		x = pos.x;
		y = pos.y + 1;
		break;
	default:
		std::cerr << "Invalid argument passed to " << __func__ << "\n";
		break;
	}

	if (isValidDirection(x, y, player, map, energy_deduction) && isEnoughEnergy(player))
	{
		player->move(direction_str[direction]);
		player->setEnergy(player->getEnergy() - energy_deduction);
	}
}

InputParser::result InputParser::checkAndParseInput(int key_stroke)
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
		case TK_Q:
			return EXIT;
		default: break;
	}

	previous_value_ = key_stroke;
	return CONTINUE;
}
