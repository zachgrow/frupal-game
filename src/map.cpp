/*   map.cpp
DATE Feb 07 2020
AUTH Zach Grow
DESC Implements the GameMap class and its associated methods
*/

#include "map.hpp"
#include "tile.hpp"
#include <iostream>

using namespace std;

GameMap::GameMap() :
mapWidth(0),
mapHeight(0),
mapArray(nullptr)
{	// The default ctor

}
//GameMap::~GameMap() { }
bool GameMap::generateMap(unsigned int inputWidth, unsigned int inputHeight) {
	// Generates a new map, given a rectangular size
	// Do nothing and return FALSE if a map has already been created
	if (this->mapWidth != 0 || this->mapHeight != 0) {
		cerr << "ERROR: Cannot overwrite existing map data.\n";
		return false;
	}
	
	return true;
}
Tile* GameMap::getTileAt(unsigned int x, unsigned int y) {


}
char GameMap::getTileSymbolAt(unsigned int x, unsigned int y) {

}
int GameMap::getTileColorAt(unsigned int x, unsigned int y) {

}
int GameMap::getTerrainCostAt(unsigned int x, unsigned int y) {

}

