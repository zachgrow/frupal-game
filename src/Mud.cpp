#include "tile.hpp"
Mud::Mud()
{
    this->symbol = '.';
    this->color = 52;
    this->movementCost = 2;
    this->obstructMovement = true;
    this->hasBeenSeen = false;
}
Mud::Mud(char c, int color)
{
    this->symbol = c;
    this->color = color;
    this->movementCost = 2;
    this->obstructMovement = true;
    this->hasBeenSeen = false;
}
void Mud::display()
{
    //SetConsoleTextAttribute(GetStdHandle(STD_INPUT_HANDLE), this->color);
    std::cout << this->symbol;
    return;
}
char Mud::getChar()
{
    return this->symbol;
}

int Mud::getColor()
{
    return this->color;
}
void Mud::setTerrainCost(int cost)
{
    this->movementCost = cost;
}
int Mud::getTerrainCost()
{
    return this->movementCost;
}
bool Mud::obstructs()
{
    return this->obstructMovement;
}
void Mud::setObstruction()
{
    this->obstructMovement = !obstructMovement;
}
bool Mud::wasObserved()
{
    return hasBeenSeen;
}