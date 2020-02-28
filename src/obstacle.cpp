/*   obstacle.cpp
AUTH Zach Grow
DATE Feb 28 2020
DESC Implements the Obstacle class, which provide the physical representations
     of game events on the world map.
*/

#include "obstacle.hpp"

using namespace std;

Obstacle::Obstacle() :
	event(nullptr)
{	}
Obstacle::Obstacle(std::string inputName, char inputSymbol, int xPos, int yPos, int inputColor) :
	Actor(inputName, inputSymbol, xPos, yPos, inputColor),
	event(nullptr)
{	}
Obstacle::~Obstacle() {
	if (event) delete event;
}

Thief::Thief(int xPos, int yPos) :
	Obstacle("(greedy tile)", 'x', xPos, yPos, 0xFF336699)
{	event = new Greedy_Tile;

}
void Thief::action(class Player& user) {
	// does nothing right now
	if (user.getPos() == this->getPos()) {
		event->react_to_player();
		event->is_active = false;
	}
}
