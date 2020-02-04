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
void Vendor::action(Player &user){
  string inp;
  cout << "Would you like to buy a tool? Y/N" << endl;//prompt the user
  getline(cin,inp);
  if(inp.compare("y")==0 || inp.compare("Y") == 0){
    cout << "What tool would you like to buy?" << endl;
    getline(cin,inp);
    if(hasTool(inp)){//check if the tool exists
      int cost = getCost(inp);
      user.buy(inp,cost);
    }
    else{//tool doesn't exist
      cerr << "No tool by that name" << endl;
      action(user);
    }
  }
  else{//user doesn't want a tool
    user.action(user);
  }
}
bool Vendor::hasTool(string tool){
  bool found = false;
  for(auto it = list.begin();it != list.end();++it){
    if(tool.compare(it->first) == 0)
      found = true;
  }
  return found;
}
void Vendor::displayTools(){
  for(auto it=list.begin();it!=list.end();++it){
    cout << "Tool: " << it->first << " Cost: " << it->second << endl;
  }
}
const Pos Vendor::getPos(){return position;}
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
    }catch(std::invalid_argument const &e){ cerr << "Bad input" << endl;}
    catch(std::out_of_range const &e){cerr << "out of range" << endl;}
  }
}
void Vendor::addTool(){
  string tool;
  cout << "What is your tool called?" << endl;
  getline(cin,tool);
  cout << "How much does your tool cost?" << endl;
  int cost;
  cin >> cost;
  if(cin.fail())
    cerr << "Bad input" << endl;
  else{
    list.insert(make_pair(tool,cost));
  }
}
int Vendor::getCost(string tool){
  for(auto it = list.begin();it != list.end();++it){
    if(tool.compare(it->first) == 0)
      return it->second;
  }
  return 0;
}
std::pair<std::string,int> Vendor::getTool(std::string title,int cost){
  auto it = list.find(make_pair(title,getCost(title)));
  if(it != list.end())
    return *it;
  else{

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
  toolbelt = user.toolbelt;
}

Player::~Player(){

}
void Player::display(){//displays the players class members
  cout << name << endl << money << endl
  << energy << endl << position.x << " " << position.y << endl;
}
void Player::displayTools(){
  for(auto it = toolbelt.begin();it != toolbelt.end();++it)
    cout << "Tool: " << *it << endl;
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

void Player::action(class Player & user){//player action takes user input and calls move or buy
  string inp;
  cout << "Where would you like to move?" << endl;
  getline(cin,inp);//get user input
  //if(inp.compare("move") == 0 || inp.compare("Move") == 0){//make comparison
    //cout << "What direction would you like to move?" << endl;
    ///getline(cin,inp);
    move(inp);//call function
  }
/*  else if(inp.compare("buy") == 0 || inp.compare("Buy") == 0){
    cout << "What tool would you like to buy?" << endl;
    getline(cin,inp);
    buy(inp);
  }
  else{//invalid input
    cerr << "Please enter Move or Buy" << endl;
    action();//restart action
  }*/
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
  bool Player::buy(string tool,int cost){//buy tool from vendor
    if(hasTool(tool)){//check for tool
      cerr << "You already have this tool" << endl;
      return false;
    }
    else{
      if(cost > money){//check cost of tool
        cerr << "You don't have enough money for that tool" << endl;
        return false;
      }
      else{
        money -= cost;//decrease money
        toolbelt.insert(tool);//add the tool
        return true;
      }
    }
  }
  bool Player::hasTool(string tool){//Loop through the users tools to make sure they don't have it
    auto it = toolbelt.find(tool);
    if(it != toolbelt.end())
      return true;
    return false;
  }
