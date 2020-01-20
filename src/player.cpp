/* player.cpp
 * Auth: Carlos Sotello
 * Desc: This file contains the imlimentation for the player class
 */
#include"player.hpp"

player::player():name(NULL),money(0),energy(0){//default constructor
  pos[0] = 0;
  pos[1] = 0;
}

player::player(int strtMoney,int strtEnergy, char * name):money(strtMoney),energy(strtEnergy){//constructor to set given values
  this->name = new char[strlen(name)+1];
  strcpy(this->name,name);
  pos[0] = 0;
  pos[1] = 0;
}
player::player(const player& user){//copy constructor
  name = new char[strlen(user.name)+1];
  strcpy(name,user.name);
  money = user.money;
  energy = user.energy;
  pos[0] = user.pos[0];
  pos[1] = user.pos[1];
}

player::~player(){
  if(name)
    delete name;
}
void player::display(){//displays the players class members
  if(name)
    cout << name << endl;
  cout << money << endl << energy << endl << pos[0] << " " << pos[1] << endl;
}

//setter functions for the class members
void player::setName(char * name){
  if(this->name)
    delete this->name;
  this->name = new char[strlen(name)+1];
  strcpy(this->name,name);
}
void player::setMoney(int money){
  this->money = money;
}
void player::setEnergy(int energy){
  this->energy = energy;
}

//getter functions
int player::getMoney(){
  return money;
}
int player::getEnergy(){
  return energy;
}

void player::action(){

}

bool player::move(char inp){//change the players position based on user input, returns true after succesful movement
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
