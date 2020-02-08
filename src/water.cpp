#include "tile.hpp"
#include <iostream>

Water::Water()
{

    this->symbol = '.';
    this->color = 14;
    this->movementCost = 1;
    this->obstructMovement = false;
    this->hasBeenSeen = false;
}
Water::Water(char c, int color)
{
    this->symbol = c;
    this->color = color;
    this->movementCost = 1;
    this->obstructMovement = false;
    this->hasBeenSeen = false;
}
void Water::display()
{
    //SetConsoleTextAttribute(GetStdHandle(STD_INPUT_HANDLE), this->color);
    std::cout << this->symbol;
    return;
}
char Water::getChar()
{
    return this->symbol;
}

int Water::getColor()
{
    return this->color;
}
void Water::setTerrainCost(int cost)
{
    this->movementCost = cost;
}
int Water::getTerrainCost()
{
    return this->movementCost;
}
bool Water::obstructs()
{
    return this->obstructMovement;
}
void Water::setObstruction()
{
    this->obstructMovement = !obstructMovement;
}
bool Water::wasObserved()
{
    return hasBeenSeen;
}
