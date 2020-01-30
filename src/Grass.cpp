#include "tile.hpp"
Grass::Grass()
{
    c = '.';
    r = 0;
    g = 255;
    b = 0;
    status = false;
}
Grass::Grass(char c, int r, int g, int b)
{
    this->c = c;
    this->r = r;
    this->g = g;
    this->b = b;
    this->status = false;
}
void Grass::display()
{
    //SetConsoleTextAttribute(GetStdHandle(STD_INPUT_HANDLE),this->color);
    std::cout << this->c << ' ';
    return;
}
char Grass::getChar()
{
    return this->c;
}
int Grass::getColor()
{
    return 0;
}