/*   map.hpp
DATE Feb 07 2020
AUTH Zach Grow
DESC Defines the GameMap class, which contains and manages map objects
*/

#ifndef FRUPALGAME_SRC_MAP_HPP_INCLUDED
#define FRUPALGAME_SRC_MAP_HPP_INCLUDED

#include "tile.hpp"

class GameMap {
	public:
		GameMap();
		~GameMap();
		bool generateMap(const unsigned int inputWidth, const unsigned int inputHeight);
		Tile* getTileAt(unsigned int x, unsigned int y);
		char getTileSymbolAt(unsigned int x, unsigned int y);
		int getTileColorAt(unsigned int x, unsigned int y);
		int getTerrainCostAt(unsigned int x, unsigned int y);

	private:
		unsigned int mapWidth;
		unsigned int mapHeight;
		Tile** mapArray;
		void debugDumpMap();

};
#endif //FRUPALGAME_SRC_MAP_HPP_INCLUDED
