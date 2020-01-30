#include "tile.hpp"

Water::Water()
{
    c = '.';
    r = 0;
    g = 0;
    b = 256;
}
Water::Water(char c, int r, int g, int b)
{
    this->c = c;
    this->r = r;
    this->g = g;
    this->b = b;
    this->status = false;
}
void Water::display()
{
    //SetConsoleTextAttribute(GetStdHandle(STD_INPUT_HANDLE), this->color);
    std::cout << this->c;
    return;
}