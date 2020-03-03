#include "tile.hpp"
#include <iostream>

Grass::Grass()
{
    this->symbol = ' ';
    this->color = 0xBB006400;
    this->movementCost = 1;
    this->obstructMovement = true;
    this->hasBeenSeen = false;
}
Grass::Grass(char c, int color)
{
    this->symbol = c;
    this->color = color;
    this->movementCost = 1;
    this->obstructMovement = false;
    this->hasBeenSeen = false;
}
void Grass::display()
{
    //SetConsoleTextAttribute(GetStdHandle(STD_INPUT_HANDLE), this->color);
    std::cout << this->symbol;
    return;
}
char Grass::getChar()
{
    return this->symbol;
}

int Grass::getColor()
{
    return this->color;
}
void Grass::setTerrainCost(int cost)
{
    this->movementCost = cost;
}
int Grass::getTerrainCost()
{
    return this->movementCost;
}
bool Grass::obstructs()
{
    return this->obstructMovement;
}
void Grass::setObstruction()
{
    this->obstructMovement = !obstructMovement;
}
bool Grass::wasObserved()
{
    return hasBeenSeen;
}
void Grass::setObserved(){
	this->hasBeenSeen=true;
}
