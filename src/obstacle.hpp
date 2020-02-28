/*   obstacle.hpp
AUTH Zach Grow
DATE Feb 28 2020
DESC Implements the Obstacle class, which provide the physical representations
     of game events on the world map.
*/

#ifndef FRUPALGAME_SRC_OBSTACLE_HPP_INCLUDED
#define FRUPALGAME_SRC_OBSTACLE_HPP_INCLUDED
#include "player.hpp"
#include "event.hpp"
#include <string>

class Obstacle : public Actor {
	public:
		Obstacle();
		Obstacle(std::string inputName, char inputSymbol, int xPos, int yPos, int inputColor);
		virtual ~Obstacle();
		virtual void action(class Player& user) = 0;
		bool isActive() { return this->event->is_active; }
	
	protected:
		Event *event;
};

class Thief : public Obstacle {
	public:
		Thief(int xPos, int yPos);
		void action(class Player& user);
};

#endif // FRUPALGAME_SRC_OBSTACLE_HPP_INCLUDED
