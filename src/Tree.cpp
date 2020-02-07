#include "tile.hpp"
#include <iostream>

Tree::Tree()
{
    this->c = '|';
    r = 0;
    g = 128;
    b = 0;
    this->status = false;
}
Tree::Tree(char c, int r, int g, int b)
{
    this->c = c;
    this->r = r;
    this->g = g;
    this->b = b;
    this->status = false;
}
void Tree::display()
{
    //SetConsoleTextAttribute(GetStdHandle(STD_INPUT_HANDLE), this->color);
    std::cout << this->c;
    return;
}
char Tree::getChar()
{
    return this->c;
}
