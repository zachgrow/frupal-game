/* player.hpp
 * Auth:Carlos Sotello
 * Desc: This is the header file for the player class which stores the users position and handles their movement and acitons.
 */

#include<iostream>
#include<cstring>
#include<cmath>

using namespace std;

struct Pos{ int x; int y;};

class Actor{//actor class acts as base class for player and vendor
public:
  virtual void action() = 0;
private:
};

class Vendor : public Actor{
public:
  Vendor();
  void action();
private:

};


class Player : public Actor{
public:
  Player();//constructors
  Player(int strtMoney,int strtEnergy,char * name);
  Player(const Player& user);
  ~Player();

  void action();//action will call relevant function

  void setName(char * name);//setter functions
  void setMoney(int money);
  void setEnergy(int energy);
  void setPos(int x, int y);

  int getMoney();//getter functions
  int getEnergy();
  char* getName();
  Pos getPos();

  void display();//display function mostly for testing
  bool move(char inp);//changes the players position based on character input
  bool buy(char tool);//ideally buys a tool if possible based on a character unique to each tool
private:
  int money;
  int energy;
  Pos position;
  string name;

};
