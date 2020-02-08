#include "tile.hpp"

Stone::Stone()
{
    this->symbol = 'O';
    this->color = 8;
    this->movementCost = 0;
    this->obstructMovement = false;
    this->hasBeenSeen = false;
}
Stone::Stone(char c, int color)
{
    this->symbol = c;
    this->color = color;
    this->movementCost = 0;
    this->obstructMovement = false;
    this->hasBeenSeen = false;
}
void Stone::display()
{
    //SetConsoleTextAttribute(GetStdHandle(STD_INPUT_HANDLE), this->color);
    std::cout << this->symbol;
    return;
}
char Stone::getChar()
{
    return this->symbol;
}

int Stone::getColor()
{
    return this->symbol;
}
void Stone::setTerrainCost(int cost)
{
    this->movementCost = cost;
}
int Stone::getTerrainCost()
{
    return this->movementCost;
}
bool Stone::obstructs()
{
    return this->obstructMovement;
}
void Stone::setObstruction()
{
    this->obstructMovement = !obstructMovement;
}
bool Stone::wasObserved()
{
    return hasBeenSeen;
}