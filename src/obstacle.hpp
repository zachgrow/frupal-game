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
		Obstacle(std::string inputName, char inputSymbol, Pos inputPosn, int inputColor);
//		~Obstacle();
		virtual void action(class Player& user);
	
	private:
		Event *event;
};
#endif // FRUPALGAME_SRC_OBSTACLE_HPP_INCLUDED
