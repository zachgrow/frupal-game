#include "tile.hpp"
#include <iostream>

Treasure::Treasure()
{
    c = 'T';
    r = 255;
    g = 255;
    b = 0;
}
Treasure::Treasure(char c, int r, int g, int b)
{
    this->c = c;
    this->r = r;
    this->g = g;
    this->b = b;
    this->status = false;
}
void Treasure::display()
{
    //SetConsoleTextAttribute(GetStdHandle(STD_INPUT_HANDLE), this->color);
    std::cout << this->c;
    return;
}
void Treasure::getAction()
{
    return;
}
void Treasure::afterAction()
{
    return;
}
