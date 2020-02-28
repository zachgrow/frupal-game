#include "event.hpp"
#include "player.hpp"
#include <iostream>

Player player;

Event::Event()
{
	is_active = true;
    is_resolved = false; 
}

void Event::greeting()
{
    cout<<"Uh-Oh You've run into a little trouble " <<endl;
    return; 
}

void Back_Track::greeting()
{
     cout<<"Uh-Oh You've run into a little trouble " <<endl;
     cout<<"You got caught in a mudslide and got moved back 3 spaces" <<endl;
     return;
}

void Back_Track::react_to_player()
{
    greeting();
    move_player();
    return;
}

bool Back_Track::move_player()
{
    //Access to player position?
    int x = player.position.x;
    int y = player.position.y;

    if(x-3 > 0)
    {
        //place holder for method to move player
        player.setPos(x-3,y);
        is_resolved= true;
        return 1;
    }
    if(x-2 > 0)
    {
        player.setPos(x-2,y);
        is_resolved= true;
        return 1;
    }
    if(x-1 > 0)
    {
        player.setPos(x-1,y);
        is_resolved= true;
        return 1;
    }
    else 
        is_resolved= true;
        return 0;
}

void Wind_Storm::greeting()
{
     cout<<"Uh-Oh You've run into a little trouble " <<endl;
     cout<<"You got caught in a tornado that lifted you up and dropped you 3 spaces away" <<endl;
     return;
}

void Wind_Storm::react_to_player()
{
    greeting();
    move_player();
    return;
}

bool Wind_Storm::move_player()
{
    //Access to player position?
    int x = player.position.x;
    int y = player.position.y;

    if(y-3 > 0)
    {
        //place holder for method to move player
        player.setPos(x,y-3);
        is_resolved= true;
        return 1;
    }
    if(y-2 > 0)
    {
        player.setPos(x,y-2);
        is_resolved= true;
        return 1;
    }
    if(y-1 > 0)
    {
        player.setPos(x,y-1);
        is_resolved= true;
        return 1;
    }
    else 
        is_resolved= true;
        return 0;
}

void Binoculars::greeting()
{
     cout<<"You sumbled upon an old pair of Binoculars " <<endl;
     cout<<"These can be used to see further ahead and watch out for upcomming obstacles" <<endl;
     return;
    
}

void Binoculars::react_to_player()
{
    greeting();
    give_Binoculars();
    return;
}

bool Binoculars::give_Binoculars()
{
    if(player.hasTool("Binoculars")==1)    
    {
        is_resolved= true;
        return 0;
    }
    else
    {
        //Find out how to add without cost 
        Vendor temp_vendor;
        int binocular_cost = temp_vendor.getCost("Binoculars");
        player.setMoney(player.getMoney() + binocular_cost);
        player.buy("Binoculars",binocular_cost);
        is_resolved= true;
        return 1;
    }
}
void Greedy_Tile::greeting()
{
     cout<<"You look down to see that your money bag has a hole in it!" <<endl;
     cout<<"Looking down into you bag, you realize that all of your money is gone!" <<endl; 
     return;
}

void Greedy_Tile::react_to_player()
{
    greeting();
    take_money();
    return;
}

bool Greedy_Tile::take_money()
{
    //place holder for accessing player
    player.setMoney(0);
    is_resolved= true;
    return 1; 
}
void Jackpot::greeting()
{
     cout<<"Someone who came before you dropped their bag of money" <<endl;
     cout<<"Congrats! This is a big break. You double your money!" <<endl; 
     return;
}

void Jackpot::react_to_player()
{
    greeting();
    give_money();
    return;
}

bool Jackpot::give_money()
{
    //place holder for accessing player
    int Jackpot = player.getMoney();
    player.setMoney(Jackpot);
    is_resolved = true;
    return 1; 
}

void Nap::greeting()
{
     cout<<"Is that a hammock?" <<endl;
     cout<<"Congrats! Take a power Nap and boost your energy by 50%" <<endl; 
     return;
}
void Nap::react_to_player()
{
    greeting();
    take_Nap();
    return;
}

bool Nap::take_Nap()
{
    int boost = player.getEnergy() *2;
    player.setEnergy(boost);
    is_resolved = true;
    return 1; 
}

void Dehydration::greeting()
{
     cout<<"You've been walking for a while" <<endl;
     cout<<"The elements are getting to you. Dehydration costs you half of your energy" <<endl; 
     return;
}

void Dehydration::react_to_player()
{
    greeting();
    dehydrate();
    return;
}

bool Dehydration::dehydrate()
{
    int loss = player.getEnergy()/2;
    player.setEnergy(loss);
    is_resolved= true;
    return 1; 
}

void Troll::greeting()
{
    cout<<"You came across a nasty Troll living on the island" <<endl;
    cout<<"In order to let you pass, he wants you to either give him half of your money or you must spend half of your energy helping him repair his hut" <<endl; 
    cout<<"Enter 'W' if you want to work, or 'M' if you want to pay him off"<<endl;
	char response;	
	cin>>response;
	response=toupper(response);
    
    if (response=='W')
        labor();
    if (response== 'M')
        steal_money();
    else
    {
        cout<<"Invalid input. Please select 'W' or 'M'" <<endl;
        greeting();
    }
    
}

void Troll::react_to_player()
{
    greeting();
    return;
}

bool Troll::labor()
{
    int loss = player.getEnergy()/2;
    player.setEnergy(loss);
    is_resolved= true;
    return 1; 
}

bool Troll::steal_money()
{
    int left_overs = player.getMoney();
    player.setMoney(left_overs);
    is_resolved= true;
    return 1;
}

void Mud_Event::greeting()
{
     cout<<"You've run into a some Mud" <<endl;
     return;
}

void Mud_Event::react_to_player()
{
    greeting();
    give_money();
    return;
}

bool Mud_Event::mud_boots()
{
    //place holder for Mud action
  
    is_resolved = true;
    return 1; 
}

void Tree_Event::greeting()
{
     cout<<"A Tree is blocking your path" <<endl;
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
    if(player.hasTool("AXE"))
    {
        cout<<"Using your axe you clear your path and continue on your way"
        is_resolved = true;
        return 1;
    }
    else
    {
        cout<<"You'll have to buy an Axe if you want to continue on this path";
        Vendor tempVendor;
        tempVendor.action(player);
        is_resolved = true;
        return 1 ;
    }
}

void Water_Event::greeting()
{
    cout<<"You've come across a river" <<endl;
    cout<<"You'll need a boat in order to cross" <<endl;
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
    if(player.hasTool("BOAT"))
    {
        cout<<"Using your boat, you cross the river safely and continue on your way"
        is_resolved = true;
        return 1;
    }
    else
    {
        cout<<"You'll have to buy an Boat if you want to continue on this path";
        Vendor tempVendor;
        tempVendor.action(player);
        is_resolved = true;
        return 1 ;
    }
}

