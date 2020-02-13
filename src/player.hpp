/* player.hpp
 * Auth:Carlos Sotello
 * Desc: This is the header file for the player class which stores the users position and handles their movement and acitons.
 */
#ifndef FRUPALGAME_SRC_PLAYER_HPP_INCLUDED
#define FRUPALGAME_SRC_PLAYER_HPP_INCLUDED

#include<iostream>
#include<cstring>
#include<cmath>
#include<fstream>
#include<set>
#include<string>
#include<sstream>
//Update when tools are implemented
const int MAX = 80;//global used for bounds checking
const char DEL = '#';//delimeter used for reading tools from file
using namespace std;
typedef std::set<std::pair<std::string,int>> tools;
struct Pos{
  int x;
  int y;
  bool operator==(const Pos & other)const;//compare two positions(player and vendor)
  friend ostream& operator<<(ostream& out, const Pos &pos);
};

class Actor{//actor class acts as base class for player and vendor
public:
  Actor();
  ~Actor();
  virtual void action(class Player& user) = 0;
  const Pos getPos();
  void setPos(int x,int y);
  int getColor();
  void setColor(int val);
  char getSymbol();
  void setSymbol(char symbol);
  string getName();
  void setName(string name);


protected:
  string name;
  char symbol;
  Pos position;
  int color;
private:

};

class Vendor : public Actor{
public:
  Vendor();
  ~Vendor();
  void action(class Player &user);
  void initialize(string file);
  void displayTools();
  void addTool();
  int getCost(string tool);
  bool hasTool(string tool);
  std::pair<std::string,int> getTool(std::string title,int cost);
private:
  tools list;
};


class Player : public Actor{
public:
  Player();//constructors
  Player(int strtMoney,int strtEnergy,string name);
  Player(const Player& user);
  ~Player();

  void action(class Player &user);//action will call relevant function

  void setMoney(int money);//setter functions
  void setEnergy(int energy);

  int getMoney();//getter functions
  int getEnergy();

  void display();//display function mostly for testing
  void displayTools();//displays the tools the user has
  bool move(string inp);//changes the players position based on Direction(North etc.)
  bool buy(string tool, int cost);//checks cost then adds tool to toolbelt and subtracts from money
  bool hasTool(string tool);//searches toolbelt for argument returns true if found
  void dropTool(string tool);//removes the arguement from toolbelt
  void addJewel();//incriment jewels
private:
  unsigned int money;
  unsigned int energy;
  unsigned int jewels;
  std::set<std::string> toolbelt;
};
#endif //FRUPALGAME_SRC_PLAYER_HPP_INCLUDED
