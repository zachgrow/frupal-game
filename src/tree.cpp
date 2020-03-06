#include "tile.hpp"

Tree::Tree()
{
    this->symbol = 'T';
    this->color = 0xBB556B2F;
    this->movementCost = 1;
    this->obstructMovement = true;
    this->hasBeenSeen = false;
}
Tree::Tree(char c, int color)
{
    this->symbol = c;
    this->color = color;
    this->movementCost = 1;
    this->obstructMovement = true;
    this->hasBeenSeen = false;
}
void Tree::display()
{
    //SetConsoleTextAttribute(GetStdHandle(STD_INPUT_HANDLE), this->color);
    std::cout << this->symbol;
    return;
}
char Tree::getChar()
{
    return this->symbol;
}

int Tree::getColor()
{
    return this->color;
}
void Tree::setTerrainCost(int cost)
{
    this->movementCost = cost;
}
int Tree::getTerrainCost()
{
    return this->movementCost;
}
bool Tree::obstructs()
{
    return this->obstructMovement;
}
void Tree::setObstruction()
{
    this->obstructMovement = !obstructMovement;
}
bool Tree::wasObserved()
{
    return hasBeenSeen;
}
void Tree::setObserved(){
	this->hasBeenSeen=true;
}
