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
const int MAX = 20;//global used for bounds checking
const char DEL = '#';//delimeter used for reading tools from file
using namespace std;
typedef std::set<std::pair<std::string,int>> tools;
struct Pos{
  Pos();
  Pos(int inputX, int inputY);
  int x;
  int y;
  bool operator==(const Pos & other)const;//compare two positions(player and vendor)
  friend ostream& operator<<(ostream& out, const Pos &pos);
};

class Actor{//actor class acts as base class for player and vendor
public:
  Actor();
  Actor(string newName, char newSymbol, int inputX, int inputY, int newColor);
  Actor(string newName, char newSymbol, Pos newPosition, int newColor);
  Actor(const Actor& other);
  ~Actor();

  virtual void action(class Player& user) = 0;

  void setPos(int x,int y);//setter
  void setColor(int val);
  void setSymbol(char symbol);
  void setName(string name);

  string getName();//getter
  char getSymbol();
  int getColor();
  const Pos getPos();

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
  Vendor(const Vendor& other);
  ~Vendor();
  void action(class Player &user);
  void initialize(string file);//read tools from file where each line is tool#cost
  void displayTools();//display the tools
  void addTool();//add tool based on user input
  void addTool(string name,unsigned int cost);//add tool based on arguments

  int getCost(string tool);//return the cost of tool
  bool getVis();//return whether the vendor is visible or not
  void setVis(bool vis);//set if the vendor is visible
  bool hasTool(string tool);//return true if tool is in list
  std::pair<std::string,int> getTool(std::string title,int cost);
private:
  bool isVisible;
  tools list;
};


class Player : public Actor{
public:
  Player();//constructors
  Player(int strtMoney,int strtEnergy,string name);
  Player(const Player& user);
  ~Player();

  void action(class Player &user);//action will call relevant function

  void setMoney(unsigned int money);//setter functions
  void setEnergy(unsigned int energy);
  bool deductEnergy(unsigned int cost);//Reduce player energy on movement
  void setVis(unsigned int vis);

  int getMoney();//getter functions
  int getEnergy();
  int getVis();

  void display();//display function mostly for testing
  void displayTools();//displays the tools the user has
  bool move(string inp);//changes the players position based on Direction(North etc.)
  bool buy(string tool, unsigned int cost);//checks cost then adds tool to toolbelt and subtracts from money
  bool hasTool(string tool);//searches toolbelt for argument returns true if found
  void dropTool(string tool);//removes the arguement from toolbelt
  void giveTool(string tool);//give the player a tool for free
  void addJewel();//incriment jewels
  std::set<std::string>* getToolbelt() { return &toolbelt; }

private:
  unsigned int money;
  unsigned int energy;
  unsigned int jewels;
  unsigned int visibility;//used for updating map
  std::set<std::string> toolbelt;
};
#endif //FRUPALGAME_SRC_PLAYER_HPP_INCLUDED
