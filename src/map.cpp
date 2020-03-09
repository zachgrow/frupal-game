/*   map.cpp
DATE Feb 07 2020
AUTH Zach Grow
DESC Implements the GameMap class and its associated methods
*/

#include "map.hpp"
#include "engine.hpp"
#include "tile.hpp"
#include <iostream>

typedef unsigned int uint;
using namespace std;

GameMap::GameMap() : mapWidth(0),
					 mapHeight(0),
					 mapArray(nullptr)
{ // The default ctor
}
GameMap::~GameMap()
{
	// The destructor
	delete[] mapArray;
}
//bool GameMap::generateMap(const uint inputWidth, const uint inputHeight, const GameEngine* engine) {
bool GameMap::generateMap(const unsigned int inputWidth, const unsigned int inputHeight, int (*rng)(int, int))
{
	// Generates a new map, given a rectangular size
	// Do nothing and return FALSE if a map has already been created
	if (this->mapWidth != 0 || this->mapHeight != 0)
	{
		cerr << "ERROR: Map object already exists.\n";
		return false;
	}
	// Simple map generation scheme: roll 1d20 and choose a Tile type:
	// 01-08	Rock
	// 09-12	Dirt
	// 13-15	Water
	// 15-20	Grass
	mapWidth = inputWidth;
	mapHeight = inputHeight;
	mapArray = new Tile *[mapWidth * mapHeight];
	// Specific values are accessed as mapArray[x * mapWidth + y]
	uint randomValue = 0;
//	clog << "Generating new map with dims " << mapWidth << "x" << mapHeight << "\n";
	for (uint mapXIndex = 0; mapXIndex < inputWidth; mapXIndex++)
	{
		for (uint mapYIndex = 0; mapYIndex < inputHeight; mapYIndex++)
		{
			// roll the dice
			randomValue = rng(1, 20);
//			clog << "randomValue: " << randomValue << endl;
			uint mapCoordinate = mapXIndex * mapWidth + mapYIndex;
			if (randomValue <= 1)
			{
				// add Rock tile
				//				mapArray[mapCoordinate] = new Rock;
				mapArray[mapCoordinate] = new Stone;
			}
			else if (randomValue <= 2)
			{
				mapArray[mapCoordinate] = new Tree;
			}
			else if (randomValue <=5)
			{
				mapArray[mapCoordinate] = new Mud;				
			}
			else if (randomValue <= 6)
			{
				// add Water tile
				mapArray[mapCoordinate] = new Water;
			}
			else
			{
				// add a Rock tile in all other cases
				mapArray[mapCoordinate] = new Grass;
			}
		}
	}
	return true;
}
Tile *GameMap::getTileAt(unsigned int x, unsigned int y)
{
	// Returns a pointer to a specific tile in the array
	return mapArray[x * mapWidth + y];
}
char GameMap::getTileSymbolAt(unsigned int x, unsigned int y)
{
	// Returns the symbol of the tile at the specified location
	return mapArray[x * mapWidth + y]->getChar();
}
int GameMap::getTileColorAt(unsigned int x, unsigned int y)
{
	// Returns the color of the tile at the specified location
//	clog << "Color at " << x << ", " << y << " is " << mapArray[x * mapWidth + y]->getColor() << endl;
	return mapArray[x * mapWidth + y]->getColor();
}
int GameMap::getTerrainCostAt(unsigned int x, unsigned int y)
{
	// Returns the terrain cost of the tile at the specified location
	return mapArray[x * mapWidth + y]->getTerrainCost();
}

// DEBUGGING FUNCTIONS
void GameMap::debugDumpMap()
{
	// Iterates across the mapArray object and writes lines to clog that
	// indicate the pattern of tiles within the array
	clog << "Doing a dump of the map tiles:\n";
	for (uint xIndex = 0; xIndex < mapWidth; xIndex++)
	{
		for (uint yIndex = 0; yIndex < mapHeight; yIndex++)
		{
			clog << mapArray[xIndex * mapWidth + yIndex]->getChar();
		}
		clog << endl;
	}
}
void GameMap::updateMap(Pos player, int visibility){
if(player.y == 0){
	for(int i=-visibility;i<=visibility;i++)
	for(int j=-visibility;j<=visibility;j++){
		if((player.x + i ) * mapWidth + (player.y + j ) < (mapWidth * mapHeight)&&j>=0){
			mapArray[(player.x + i ) * mapWidth + (player.y + j )]->setObserved();
		}
	}
	return;
}
else if(player.y==mapHeight-1){
	for(int i=-visibility;i<=visibility;i++)
	for(int j=-visibility;j<=visibility;j++){
		if((player.x + i ) * mapWidth + (player.y + j ) < (mapWidth * mapHeight)&&j<=0){
			mapArray[(player.x + i ) * mapWidth + (player.y + j )]->setObserved();
		}
	}
	return;
}
else
for(int i=-visibility;i<=visibility;i++)
	for(int j=-visibility;j<=visibility;j++){
		if((player.x + i ) * mapWidth + (player.y + j ) < (mapWidth * mapHeight)){
			mapArray[(player.x + i ) * mapWidth + (player.y + j )]->setObserved();
		}
	}
}
bool GameMap::getObserved(unsigned int x, unsigned int y){
	return mapArray[x * mapWidth + y]->wasObserved();
}
bool GameMap::isObstructed(unsigned int x, unsigned int y){
	if(x<0 ||y<0||x>=mapWidth||y>=mapHeight)
	return false;
	return mapArray[x * mapWidth + y]->obstructs();
}
void GameMap::destroyTile(unsigned int x, unsigned int y){
	free(mapArray[x*mapWidth +y]);
	mapArray[x*mapWidth +y]= new Grass;
	return;
}
void GameMap::generateImportantStuff(unsigned int x, unsigned int y){
	for (int i = -1;i<=1;i++)
	for(int j=-1;j<=1;j++)
		if((x+i)*mapWidth + (y+j)<(mapWidth * mapHeight))
			destroyTile(x+i,y+j);
}
