#ifndef FRUPALGAME_SRC_TILE_HPP_INCLUDED
#define FRUPALGAME_SRC_TILE_HPP_INCLUDED
#include <iostream>
using namespace std;
class Tile
{
public:
    virtual void display() = 0;
    virtual char getChar() = 0;
    virtual int getColor() = 0;
    virtual void setTerrainCost(int cost) = 0;
    virtual int getTerrainCost() = 0;
    virtual bool obstructs() = 0;
    virtual void setObstruction() = 0;
    virtual bool wasObserved() = 0;
    virtual void setObserved() = 0;
    virtual int getTile()=0;

<<<<<<< HEAD
#include <string>
#include <vector>

class Tile {
    public:
    std::string obstacle;
=======
private:
    char symbol;
    int color;
    int movementCost;
    bool obstructMovement;
    bool hasBeenSeen;
>>>>>>> master
};
class Grass : public Tile
{
private:
    char symbol;
    int color;
    int movementCost;
    bool obstructMovement;
    bool hasBeenSeen;

public:
    Grass();
    Grass(char symbol, int color);
    void display();
    char getChar();
    int getColor();
    void setTerrainCost(int cost);
    int getTerrainCost();
    bool obstructs();
    void setObstruction();
    bool wasObserved();
    void setObserved();
    int getTile(){return 0;};
};
class Water : public Tile
{
private:
    char symbol;
    int color;
    int movementCost;
    bool obstructMovement;
    bool hasBeenSeen;

public:
    Water();
    Water(char symbol, int color);
    void display();
    char getChar();
    int getColor();
    void setTerrainCost(int cost);
    int getTerrainCost();
    bool obstructs();
    void setObstruction();
    bool wasObserved();
    void setObserved();
    int getTile(){return 1;};
};
struct Tree : public Tile
{
private:
    char symbol;
    int color;
    int movementCost;
    bool obstructMovement;
    bool hasBeenSeen;

public:
    Tree();
    Tree(char symbol, int color);
    void display();
    char getChar();
    int getColor();
    void setTerrainCost(int cost);
    int getTerrainCost();
    bool obstructs();
    void setObstruction();
    bool wasObserved();
    void setObserved();
    int getTile(){return 2;}
};

struct Mud : public Tile
{
private:
    char symbol;
    int color;
    int movementCost;
    bool obstructMovement;
    bool hasBeenSeen;

public:
    Mud();
    Mud(char symbol, int color);
    void display();
    char getChar();
    int getColor();
    void setTerrainCost(int cost);
    int getTerrainCost();
    bool obstructs();
    void setObstruction();
    bool wasObserved();
    void setObserved();
    int getTile(){return 3;}
};

struct Stone : public Tile
{
private:
    char symbol;
    int color;
    int movementCost;
    bool obstructMovement;
    bool hasBeenSeen;

public:
    Stone();
    Stone(char symbol, int color);
    void display();
    char getChar();
    int getColor();
    void setTerrainCost(int cost);
    int getTerrainCost();
    bool obstructs();
    void setObstruction();
    bool wasObserved();
    void setObserved();
    int getTile(){return 4;}
};
struct QuickSand : public Tile
{
private:
    char symbol;
    int color;
    int movementCost;
    bool obstructMovement;
    bool hasBeenSeen;

public:
    QuickSand();
    QuickSand(char symbol, int color);
    void display();
    char getChar();
    int getColor();
    void setTerrainCost(int cost);
    int getTerrainCost();
    bool obstructs();
    void setObstruction();
    bool wasObserved();
    void setObserved();
    int getTile(){return 5;}
};
#endif // FRUPALGAME_SRC_TILE_HPP_INCLUDED
