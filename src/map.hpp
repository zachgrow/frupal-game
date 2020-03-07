/*   map.hpp
DATE Feb 07 2020
AUTH Zach Grow
DESC Defines the GameMap class, which contains and manages map objects
*/

#ifndef FRUPALGAME_SRC_MAP_HPP_INCLUDED
#define FRUPALGAME_SRC_MAP_HPP_INCLUDED

#include "tile.hpp"
#include "player.hpp"

class GameMap
{
public:
	GameMap();
	~GameMap();
	//		bool generateMap(const unsigned int inputWidth, const unsigned int inputHeight);
	bool generateMap(const unsigned int inputWidth, const unsigned int inputHeight, int (*rng)(int, int));
	Tile *getTileAt(unsigned int x, unsigned int y);
	char getTileSymbolAt(unsigned int x, unsigned int y);
	int getTileColorAt(unsigned int x, unsigned int y);
	int getTerrainCostAt(unsigned int x, unsigned int y);
	unsigned int getWidth() { return mapWidth; }
	unsigned int getHeight() { return mapHeight; }
	void updateMap(Pos player, int visibility);
	bool getObserved(unsigned int x, unsigned int y);
	bool getObstruct(unsigned int x, unsigned int y);
	int getTile(unsigned int x, unsigned int y){ return mapArray[x * mapWidth + y]->getTile();};
	void destroyTile(unsigned int x, unsigned int y);// use to destroy the obstacle tile, and replace it with grass
	void generateImportantStuff(unsigned int x, unsigned int y);// when generate important stuff, use this to clear 1 cell away from it to ensure the object is not trapped.
private:
	unsigned int mapWidth;
	unsigned int mapHeight;
	Tile **mapArray;

	void debugDumpMap();
};
#endif //FRUPALGAME_SRC_MAP_HPP_INCLUDED
