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
//Update when tools are implemented
const int TOOLCOUNT = 5;//global used for size of players tool array
const int MAX = 20;//global used for bounds checking
const char DEL = '#';//delimeter used for reading tools from file
using namespace std;
typedef std::set<std::pair<std::string,int>> tools;
struct Pos{
  int x;
  int y;
  bool operator==(const Pos & other);//compare two positions(player and vendor)
  friend ostream& operator<<(ostream& out, const Pos &pos);
};

class Actor{//actor class acts as base class for player and vendor
public:
  virtual void action(const Player& user) = 0;

private:

};

class Vendor : public Actor{
public:
  Vendor();
  void action(const Player &user);
  void initialize(string file);
  void displayTools();
  void addTool();
  int getCost(string tool);
  const Pos getPos();
  bool hasTool(string tool);
  std::pair<std::string,int> getTool(std::string title,int cost);
private:
  Pos position;
  //string tools[TOOLCOUNT];
  tools list;
};


class Player : public Actor{
public:
  Player();//constructors
  Player(int strtMoney,int strtEnergy,string name);
  Player(const Player& user);
  ~Player();

  void action();//action will call relevant function

  void setName(string name);//setter functions
  void setMoney(int money);
  void setEnergy(int energy);
  void setPos(int x, int y);

  int getMoney();//getter functions
  int getEnergy();
  string getName();
  const Pos getPos();

  void display();//display function mostly for testing
  void displayTools();
  bool move(string inp);//changes the players position based on character input
  bool buy(string tool, int cost);//ideally buys a tool if possible based on a character unique to each tool
  bool hasTool(string tool);
private:
  int money;
  int energy;
  Pos position;
  string name;
  //string tools[TOOLCOUNT];
  std::set<std::string> toolbelt;
};
#endif //FRUPALGAME_SRC_PLAYER_HPP_INCLUDED
