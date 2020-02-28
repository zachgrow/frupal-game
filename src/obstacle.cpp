/*   obstacle.cpp
AUTH Zach Grow
DATE Feb 28 2020
DESC Implements the Obstacle class, which provide the physical representations
     of game events on the world map.
*/

#include "obstacle.hpp"

using namespace std;

Obstacle::Obstacle()
{	}
Obstacle::Obstacle(std::string inputName, char inputSymbol, Pos inputPosn, int inputColor) :
	Actor(inputName, inputSymbol, inputPosn, inputColor)
{	}
