/* player.cpp
 * Auth: Carlos Sotello
 * Desc: This file contains the imlimentation for the player class
 */
#include"player.hpp"
Vendor::Vendor(){}
void Vendor::action(){}

Player::Player():name(NULL),money(0),energy(0){//default constructor
  position.x = 0;
  position.y = 0;
}

Player::Player(int strtMoney,int strtEnergy, char * name):money(strtMoney),energy(strtEnergy){//constructor to set given values
  this->name = new char[strlen(name)+1];
  strcpy(this->name,name);
  position.x = 0;
  position.y = 0;
}
Player::Player(const Player& user){//copy constructor
  name = new char[strlen(user.name)+1];
  strcpy(name,user.name);
  money = user.money;
  energy = user.energy;
  position.x = user.position.x;
  position.y = user.position.y;
}

Player::~Player(){
  if(name)
    delete name;
}
void Player::display(){//displays the players class members
  if(name)
    cout << name << endl;
  cout << money << endl << energy << endl << position.x << " " << position.y << endl;
}

//setter functions for the class members
void Player::setName(char * name){
  if(this->name)
    delete this->name;
  this->name = new char[strlen(name)+1];
  strcpy(this->name,name);
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
char* Player::getName(){
  return name;
}
Pos Player::getPos(){
  return position;
}

void Player::action(){

}

bool Player::move(char inp){//change the players position based on user input, returns true after succesful movement
  switch(inp){
    case('w'):
      pos[0]--;
      return true;
    case('a'):
      pos[1]--;
      return true;
    case('s'):
      pos[0]++;
      return true;
    case('d'):
      pos[1]++;
      return true;
    default:return false;
  }
}
