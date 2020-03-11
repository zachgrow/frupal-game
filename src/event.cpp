#include "event.hpp"
#include "player.hpp"
#include <iostream>

// Required for definition of a static member
Player *Event::player = nullptr;
void (*Event::writeMsg)(const std::string&);

Event::Event()
{
	is_active = true;
    is_resolved = false; 
}

void Event::setPlayerPtr(Player *inputPlayer)
{
	Event::player = inputPlayer;
}

void Event::setMsgLogPtr(void (*writeMsgPtr)(const string&))
{
	Event::writeMsg = writeMsgPtr;
}

void Event::greeting()
{
//    cout<<"Uh-Oh You've run into a little trouble " <<endl;
	writeMsg("Uh-Oh You've run into a little trouble ");
    return; 
}

void Back_Track::greeting()
{
     //cout<<"Uh-Oh You've run into a little trouble " <<endl;
     writeMsg("You got caught in a mudslide and got moved back 3 spaces");
     return;
}

void Back_Track::react_to_player()
{
    greeting();
    move_player();
    return;
}

bool Back_Track::move_player()//Moves player back three spaces if possible 
{
    //Access to player position
	Pos position = player->getPos();
    int newX = position.x - 3;
    int newY = position.y;
    player->setPos(newX,newY);
    is_resolved = true;
     
	return true;
}

void Wind_Storm::greeting()
{
     //cout<<"Uh-Oh You've run into a little trouble " <<endl;
     writeMsg("You got caught in a tornado that lifted you up and dropped you 3 spaces away");
     return;
}

void Wind_Storm::react_to_player()
{
    greeting();
    move_player();
    return;
}

bool Wind_Storm::move_player()//Moves player down three spaces if possible
{
    //Access to player position
    Pos position = player->getPos();
    int newX = position.x;
    int newY = position.y - 3;
    player->setPos(newX,newY);
    is_resolved = true;
     
	return true;
}

void Binoculars::greeting()
{
     writeMsg("You sumbled upon an old pair of Binoculars ");
     writeMsg("These can be used to see further ahead and watch out for upcomming obstacles");
     return;
}

void Binoculars::react_to_player()
{
    greeting();
    give_binoculars();
    return;
}

bool Binoculars::give_binoculars()//Calculates cost and gives needed money to purchase binoculars
{
    if(player->hasTool("Binoculars")==1)    
    {
        is_resolved= true;
        return 0;
    }
    else
    {
        //Find out how to add without cost 
        Vendor temp_vendor;
        int binocular_cost = temp_vendor.getCost("Binoculars");
        player->setMoney(player->getMoney() + binocular_cost);
        player->buy("Binoculars",binocular_cost);
        is_resolved= true;
        return 1;
    }
}
void Greedy_Tile::greeting()
{
     writeMsg("You look down to see that your money bag has a hole in it!");
	 writeMsg("Looking down into you bag, you realize that half of your money is gone!");
     return;
}

void Greedy_Tile::react_to_player()
{
    greeting();
    take_money();
    return;
}

bool Greedy_Tile::take_money()//Greedy tile requirement takes all of the money
{
    //place holder for taking half of the money
    player->setMoney((player->getMoney() / 2));
    //place holder for taking all of the money 
    //player->setMoney(0);
    is_resolved= true;
    return 1; 
}
void Jackpot::greeting()
{
     writeMsg("Someone who came before you dropped their bag of money");
     writeMsg("Congrats! This is a big break. You double your money!"); 
     return;
}

void Jackpot::react_to_player()
{
    greeting();
    give_money();
    return;
}

bool Jackpot::give_money()//Doubles the players' money
{
    //place holder for accessing player
    int Jackpot = player->getMoney();
    player->setMoney(Jackpot);
    is_resolved = true;
    return 1; 
}

void Nap::greeting()
{
     writeMsg("Is that a hammock?");
     writeMsg("Congrats! Take a power Nap and boost your energy by 50%"); 
     return;
}
void Nap::react_to_player()
{
    greeting();
    take_nap();
    return;
}

bool Nap::take_nap()//Doubles player's energy
{
    int boost = player->getEnergy() *2;
    player->setEnergy(boost);
    is_resolved = true;
    return 1; 
}

void Dehydration::greeting()
{
     writeMsg("You've been walking for a while");
     writeMsg("The elements are getting to you. Dehydration costs you half of your energy"); 
     return;
}

void Dehydration::react_to_player()
{
    greeting();
    dehydrate();
    return;
}

bool Dehydration::dehydrate()//Takes half of the player's energy
{
    int loss = player->getEnergy()/2;
    player->setEnergy(loss);
    is_resolved= true;
    return 1; 
}

void Troll::greeting()
{
    writeMsg("You came across a nasty Troll living on the island");
    writeMsg("In order to let you pass, he wants you to either give him half of your money or you must spend half of your energy helping him repair his hut"); 
    writeMsg("Enter 'W' if you want to work, or 'M' if you want to pay him off");
	char response;	
	cin>>response;
	response=toupper(response);
    
    if (response=='W')
    {
        labor();
        return;
    }
    if (response== 'M')
    {
        steal_money();
        return;
    }
    else
    {
        writeMsg("Invalid input. Please select 'W' or 'M'");
        greeting();
    }
    
}

void Troll::react_to_player()
{
    greeting();
    return;
}

bool Troll::labor()//Take's half of the player's energy
{
    int loss = player->getEnergy()/2;
    player->setEnergy(loss);
    is_resolved= true;
    return 1; 
}

bool Troll::steal_money()//Take's half of the player's energy
{
    int left_overs = player->getMoney();
    player->setMoney(left_overs);
    is_resolved= true;
    return 1;
}

void Tree_Event::greeting()
{
     writeMsg("A Tree is blocking your path");
     return;
}

void Tree_Event::react_to_player()
{
    greeting();
    chop();
    return;
}

bool Tree_Event::chop()
{
    //place holder for accessing player
    if(player->hasTool("AXE"))
    {
        writeMsg("Using your axe you clear your path and continue on your way");
        is_resolved = true;
        return 1;
    }
    else
    {
        writeMsg("You'll have to buy an Axe if you want to continue on this path");
    
        return 1 ;
    }
}

void Water_Event::greeting()
{
    writeMsg("You've come across a river");
    writeMsg("You'll need a boat in order to cross");
    return;
}

void Water_Event::react_to_player()
{
    greeting();
    boating();
    return;
}

bool Water_Event::boating()
{
    //place holder for accessing player
    if(player->hasTool("BOAT"))
    {
        writeMsg("Using your boat, you cross the river safely and continue on your way");
        is_resolved = true;
        return 1;
    }
    else
    {
        //Since vendor is accessible from anywhere on map, just give message
        writeMsg("You'll have to buy an Boat if you want to continue on this path");
        is_resolved = true;
        return 1 ;
    }
}

