/* player.cpp
 * Auth: Carlos Sotello
 * Desc: This file contains the imlimentation for the player class
 */
#include"player.hpp"
Pos::Pos() : x(0), y(0) {	}
Pos::Pos(int inputX, int inputY) :
	x(inputX),
	y(inputY)
{	}
bool Pos::operator==(const Pos & other)const{//compare two positions
  //ideal use:if(player.getPos() == vendor.getPos()){vendor.action(player)}
  return x == other.x && y == other.y;
}
ostream& operator<<(ostream & out, const Pos & pos){//display position
  out << "Current position[" << pos.x << ',' << pos.y << ']' << endl;
  return out;
}
Actor::Actor(){}
Actor::Actor(string newName, char newSymbol, int inputX, int inputY, int newColor) :
	name(newName),
	symbol(newSymbol),
	position(inputX, inputY),
	color(newColor)
{	}
Actor::Actor(string newName, char newSymbol, Pos newPosition, int newColor) :
	name(newName),
	symbol(newSymbol),
	position(newPosition),
	color(newColor)
{	}
Actor::Actor(const Actor& other){
  name = other.name;
  position.x = other.position.x;
  position.y = other.position.y;
  symbol = other.symbol;
  color = other.color;
}
Actor::~Actor(){}
void Actor::setPos(int x, int y){
  position.x = x;
  position.y = y;
}
void Actor::setName(string name){ this->name = name;}
void Actor::setColor(int val){color = val;}
void Actor::setSymbol(char symbol){this->symbol = symbol;}

string Actor::getName(){return name;}
const Pos Actor::getPos(){return position;}
int Actor::getColor(){return color;}
char Actor::getSymbol(){return symbol;}

Vendor::Vendor():isVisible(false){
  position.x = 0;
  position.y = 0;
  setSymbol('V');
  initialize("src/tools.txt");
}
Vendor::Vendor(const Vendor& other):Actor(other){
  list = other.list;
}
Vendor::~Vendor(){}
void Vendor::action(Player &user){//when player position and vendor position are equal
  //give the player a chance to buy a tool
  string inp;
  cout << "Would you like to buy a tool? Y/N" << endl;//prompt the user
  getline(cin,inp);
  if(inp.compare("y")==0 || inp.compare("Y") == 0){
    cout << "What tool would you like to buy?" << endl;
    displayTools();
    getline(cin,inp);
    if(hasTool(inp)){//check if the tool exists
      if(!user.buy(inp,getCost(inp)))//buy the tool: fails if player doesn't have enough money
        action(user);//if buy fails restart action
    }
    else{//tool doesn't exist
      cerr << "No tool by that name" << endl;
      action(user);//restart action
    }
  }
  cout << "Please return to other terminal" << endl; 
    
}
bool Vendor::hasTool(string tool){//check the tools list for tool
  bool found = false;
  for(auto it = list.begin();it != list.end();++it){//loop through set
    if(tool.compare(it->first) == 0)
      found = true;
  }
  return found;
}

void Vendor::displayTools(){//display the vendor tools for user/testing
  for(auto it=list.begin();it!=list.end();++it){
    cout << "Tool: " << it->first << " Cost: " << it->second << endl;
  }
}
//const Pos Vendor::getPos(){return position;}
void Vendor::initialize(string file){//read tools from a file with format tool#cost one tool per line
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
        int mid = line.find(DEL);//find the delimeter
        string tool = line.substr(0,mid);//seperate the string
        int cost = stoi(line.substr(mid+1,line.length()-mid));
        list.insert(make_pair(tool,cost));//insert the tool
      }
    }catch(std::invalid_argument const &e){ cerr << "Bad input" << endl;}
    catch(std::out_of_range const &e){cerr << "out of range" << endl;}
  }
}
void Vendor::addTool(){//add tool based on user input
  string tool;
  cout << "What is your tool called?" << endl;
  getline(cin,tool);
  cout << "How much does your tool cost?" << endl;
  int cost;
  string inp;
  getline(cin,inp);
  std::istringstream iss(inp);
  iss >> cost;
  if(cost < 0)
    cerr << "Bad input" << endl;
  else{
    list.insert(make_pair(tool,cost));
  }
}
void Vendor::addTool(string name,unsigned int cost){
  list.insert(make_pair(name,cost));
}
int Vendor::getCost(string tool){//return the cost of a tool based on name
  for(auto it = list.begin();it != list.end();++it){
    if(tool.compare(it->first) == 0)
      return it->second;
  }
  return 0;
}
std::pair<std::string,int> Vendor::getTool(std::string title,int cost){//return a pair used for a tool
  auto it = list.find(make_pair(title,getCost(title)));
  if(it != list.end())
    return *it;
  else{
    cerr << "Tool could not be found" << endl;
    return make_pair("NULL",0);
  }
}

Player::Player():money(0),energy(0),jewels(0),visibility(1){//default constructor
  position.x = 0;
  position.y = 0;
}

Player::Player(int strtMoney,int strtEnergy, string name):money(strtMoney),energy(strtEnergy),visibility(1){//constructor to set given values
  this->name = name;
  position.x = 0;
  position.y = 0;

}
Player::Player(const Player& user):Actor(user){//copy constructor
  money = user.money;
  energy = user.energy;
  jewels = user.jewels;
  toolbelt = user.toolbelt;
  visibility = user.visibility;
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

//setter functions
void Player::setMoney(unsigned int money){
  this->money = money;
}
void Player::setEnergy(unsigned int energy){
  this->energy = energy;
}
void Player::setVis(unsigned int vis){
  visibility = vis;
}
bool Player::deductEnergy(unsigned int cost){//reduce player energy on movement
  //returns false if player has run out of energy ideally ending the game
  if(cost >= 0 && energy - cost > 0){
    energy -= cost;
    return true;
  }
  return false;
}

//getter functions
int Player::getMoney(){
  return money;
}
int Player::getEnergy(){
  return energy;
}
int Player::getVis(){
  return visibility;
}

void Player::action(class Player & user){//player action takes user input and calls move or buy
  string inp;
  cout << "Where would you like to move?" << endl;
  getline(cin,inp);//get user input
  move(inp);//call function
  }

bool Player::move(string inp){//change the players position based on user input, returns true after succesful movement
//     Add energy cost based on tiles
    if(inp.compare("North") == 0 || inp.compare("north") == 0){
      if(position.x > 1){
        position.x--;
        return true;
      }
      else{
        cerr << "Cannot move West" << endl;
        return false;
      }
    }
    else if(inp.compare("West") == 0 || inp.compare("west") == 0){
      if(position.y > 1){
        position.y--;
        return true;
      }
      else{
        cerr << "Cannot move North" << endl;
        return false;
      }

    }
    else if(inp.compare("South") == 0 || inp.compare("south") == 0){
      if(position.x < MAX){
        position.x++;
        return true;
      }
      else{
        cerr << "Cannot move East" << endl;
        return false;
      }
    }
    else if(inp.compare("East") == 0 || inp.compare("east") == 0){
      if(position.y < MAX){
        position.y++;
        return true;
      }
      else{
        cerr << "Cannot move South" << endl;
        return false;
      }
    }
    else{
      cerr << "Please enter North, South, East, or West." << endl;
      getline(cin, inp);//get new user input
      return move(inp);
    }
  }
  bool Player::buy(string tool,unsigned int cost){//buy tool from vendor
    if(hasTool(tool)){//check for tool
      cerr << "You already have this tool" << endl;
      return false;
    }
    else{
      if(cost > money || money < 0){//check cost of tool
        cerr << "You don't have enough money for that tool" << endl;
        return false;
      }
      else{
        money -= cost;//decrease money
        toolbelt.insert(tool);//add the tool
        if(tool.compare("binoculars") == 0)
          visibility = 2;
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
  void Player::dropTool(string tool){//Removes tool from toolbelt
    auto it = toolbelt.find(tool);
    if(it != toolbelt.end()){
      toolbelt.erase(it);
      if((*it).compare("binoculars") == 0)//check if the tool is binoculars
        visibility = 1;
    }
    else
      cerr << "You don't have that tool" << endl;
  }
  void Player::giveTool(string tool){//give the player a free tool
    if(!hasTool(tool))
      toolbelt.insert(tool);
  }
  void Player::addJewel(){++jewels;}
