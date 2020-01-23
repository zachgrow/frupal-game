/* player.cpp
 * Auth: Carlos Sotello
 * Desc: This file contains the imlimentation for the player class
 */
#include"player.hpp"
const TOOLCOUNT = 5;
Vendor::Vendor(){}
void Vendor::action(){}

Player::Player():name(NULL),money(0),energy(0){//default constructor
  position.x = 0;
  position.y = 0;
  tools = new string[TOOLCOUNT];
}

Player::Player(int strtMoney,int strtEnergy, string name):money(strtMoney),energy(strtEnergy){//constructor to set given values
  this->name = name;
  position.x = 0;
  position.y = 0;
  tools = new string[TOOLCOUNT];
}
Player::Player(const Player& user){//copy constructor
  this->name = user.name;
  money = user.money;
  energy = user.energy;
  position.x = user.position.x;
  position.y = user.position.y;
  for(int i = 0; i < TOOLCOUNT; i++){
    tools[i] = user.tools[i];
  }
}

Player::~Player(){

}
void Player::display(){//displays the players class members
  cout << name << endl << money << endl
  << energy << endl << position.x << " " << position.y << endl;
}

//setter functions for the class members
void Player::setName(string name){
  this->name = name;
}
void Player::setMoney(int money){
  this->money = money;
}
void Player::setEnergy(int energy){
  this->energy = energy;
}
void Player::setPos(int x, int y){
  position.x = x;
  position.y = y;
}

//getter functions
int Player::getMoney(){
  return money;
}
int Player::getEnergy(){
  return energy;
}
string Player::getName(){
  return name;
}
Pos Player::getPos(){
  return position;
}

void Player::action(){//player action takes user input and calls move or buy
  string inp;
  cout << "What would you like to move or buy a tool?" << endl;
  cin.get(inp,100,'\n');
  cin.ignore(10,'\n');
  if(inp.compare("move") == 0 || inp.compare("Move") == 0){
    inp = "";
    cout << "What direction would you like to move?" << endl;
    cin.get(inp,100,'\n');
    cin.ignore(10,'\n');
    move(inp);
  }
  else if(inp.compare("buy") == 0 || inp.compare("Buy") == 0){
    inp = "";
    cout << "What tool would you like to buy?" << endl;
    cin.get(inp,100,'\n');
    cin.ignore(10,'\n');
    buy(inp);
    }
  else{
    cerr << "Please enter Move or Buy" << endl;
    }
}

bool Player::move(string inp){//change the players position based on user input, returns true after succesful movement
    if(inp.compare("North") == 0 || inp.compare("north") == 0){
      position.x--;
      return true;
    }
    else if(inp.compare("West") == 0 || inp.compare("west") == 0){
      position.y--;
      return true;
    }
    else if(inp.compare("South") == 0 || inp.compare("south") == 0){
      position.x++;
      return true;
    }
    else if(inp.compare("East") == 0 || inp.compare("east") == 0){
      position.y++;
      return true;
    }
    else{
      cerr << "Please enter North, South, East, or West." << endl;
      return false;
    }
  }
  bool Player::buy(string tool){
    if(hasTool(tool)){
      cerr << "You already have this tool" << endl;
      return false;
    }
    else{
      //buy the tool from the vendor
      return true;
    }
  }
  bool Player::hasTool(string tool){
    bool found = false;
    for(int i = 0; i < TOOLCOUNT; i++){
      if(tools[i] == tool)
        found = true;
    }
    return found;
  }
