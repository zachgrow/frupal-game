/* player.cpp
 * Auth: Carlos Sotello
 * Desc: This file contains the imlimentation for the player class
 */
#include"player.hpp"
bool Pos::operator==(const Pos & other){
  return x == other.x && y == other.y;
}
ostream& operator<<(ostream & out, const Pos & pos){
  out << "Current position[" << pos.x << ',' << pos.y << ']' << endl;
  return out;
}

Vendor::Vendor(){}
void Vendor::action(){}
void Vendor::displayTools(){
  for(auto it=list.begin();it!=list.end();++it){
    cout << "Tool: " << it->first << " Cost: " << it->second << endl;
  }
}
void Vendor::initialize(string file){
  ifstream inFile;
  inFile.open(file);
  if(!inFile){
    cerr << "Could not open file" << endl;
    return;
  }
  else{
    try{
      string line;
      while(getline(inFile,line)){
        int mid = line.find(DEL);
        string tool = line.substr(0,mid);
        int cost = stoi(line.substr(mid+1,line.length()-mid));
        list.insert(make_pair(tool,cost));
      }
    }catch(std::invalid_agument &e){ cout << "Bad input" << endl;}
    catch(std::out_of_range &e){cout << "out of range" << endl;}
  }
}

Player::Player():money(0),energy(0){//default constructor
  position.x = 0;
  position.y = 0;
}

Player::Player(int strtMoney,int strtEnergy, string name):money(strtMoney),energy(strtEnergy){//constructor to set given values
  this->name = name;
  position.x = 0;
  position.y = 0;

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
const Pos Player::getPos(){
  return position;
}

void Player::action(){//player action takes user input and calls move or buy
  string inp;
  cout << "Would you like to move or buy a tool?" << endl;
  getline(cin,inp);//get user input
  if(inp.compare("move") == 0 || inp.compare("Move") == 0){//make comparison
    cout << "What direction would you like to move?" << endl;
    getline(cin,inp);
    move(inp);//call function
  }
  else if(inp.compare("buy") == 0 || inp.compare("Buy") == 0){
    cout << "What tool would you like to buy?" << endl;
    getline(cin,inp);
    buy(inp);
    }
  else{//invalid input
    cerr << "Please enter Move or Buy" << endl;
    action();//restart action
    }
}

bool Player::move(string inp){//change the players position based on user input, returns true after succesful movement
//     Add energy cost based on tiles
    if(inp.compare("North") == 0 || inp.compare("north") == 0){
      if(position.x > 0){
        position.x--;
        return true;
      }
      else{
        cerr << "Cannot move North" << endl;
        return false;
      }
    }
    else if(inp.compare("West") == 0 || inp.compare("west") == 0){
      if(position.y > 0){
        position.y--;
        return true;
      }
      else{
        cerr << "Cannot move West" << endl;
        return false;
      }

    }
    else if(inp.compare("South") == 0 || inp.compare("south") == 0){
      if(position.x < MAX){
        position.x++;
        return true;
      }
      else{
        cerr << "Cannot move South" << endl;
        return false;
      }
    }
    else if(inp.compare("East") == 0 || inp.compare("east") == 0){
      if(position.y < MAX){
        position.y++;
        return true;
      }
      else{
        cerr << "Cannot move East" << endl;
        return false;
      }
    }
    else{
      cerr << "Please enter North, South, East, or West." << endl;
      getline(cin, inp);//get new user input
      return move(inp);
    }
  }
  bool Player::buy(string tool){//buy tool from vendor
    if(hasTool(tool)){//check for tool
      cerr << "You already have this tool" << endl;
      return false;
    }
    else{
      //buy the tool from the vendor
      //Maybe this calls or gets called by vendor.action()
      return true;
    }
  }
  bool Player::hasTool(string tool){//Loop through the users tools to make sure they don't have it
    bool found = false;
    for(int i = 0; i < TOOLCOUNT; i++){
      if(tools[i].compare(tool) == 0)
        found = true;
    }
    return found;
  }
