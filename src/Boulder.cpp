#include "tile.hpp"

Boulder::Boulder()
{
    c = 'B';
    r = 128;
    g = 128;
    b = 128;
}
Boulder::Boulder(char c, int r, int g, int b)
{
    this->c = c;
    this->r = r;
    this->g = g;
    this->b = b;
    this->status = false;
}
void Boulder::display()
{
    //SetConsoleTextAttribute(GetStdHandle(STD_INPUT_HANDLE), this->color);
    std::cout << this->c;
    return;
}
void Boulder::getAction()
{
    return;
}
void Boulder::afterAction()
{
    return;
}
int Boulder::getColor()
{
    return 0;
}