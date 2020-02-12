#include "event.hpp"
#include <iostream>

Event::Event()
{
	is_active=0;
    is_resolved=0; 
}

void Event::greeting()
{
    cout<<"Uh-Oh You've run into a little trouble " <<endl;
}

bool Event::react_to_player()
{
    cout<<"Would you like to proceede with this challenge? (Y/N) "<<endl;
	char response;	
	cin>>response;
	response=toupper(response);
    
    if (response=='N')
    {
        is_resolved=0;
        return 0;
    }
    else
    {
        is_resolved=1;
        return 1;
    }
    
}

void back_track::greeting()
{
     cout<<"Uh-Oh You've run into a little trouble " <<endl;
     cout<<"You got caught in a mudslide and got moved back 3 spaces" <<endl;
}

bool back_track::move_player()
{
    //Access to player?
    if(player->position.x-3 > 0)
    {
        //place holder for method to move player
        player->position.x-3;
        //this->position.x -3;
        //player.move()
        is_resolved=1;
        return 1;
    }
    if(player->position.x-2 > 0)
    {
        player->position.x-2;
        is_resolved=1;
        return 1;
    }
    if(player->position.x-1 > 0)
    {
        player->position.x-1;
        is_resolved=1;
        return 1;
    }
    else 
        is_resolved=0;
        return 0;
}

void binoculars::greeting()
{
     cout<<"You sumbled upon an old pair of binoculars " <<endl;
     cout<<"These can be used to see further ahead and watch out for upcomming obstacles" <<endl;
    
}

bool binoculars::give_binoculars()
{
    if(player.hasTool("binoculars")==1)    
    {
        is_resolved=1;
        return 0;
    }
    else
    {
        //Find out how to add without cost 
        player.addTool();
        is_resolved=1;
        return 1;
    }
}
void greedy_tile::greeting()
{
     cout<<"You bumped into a greedy troll!" <<endl;
     cout<<"He takes half of your money as a toll and sends you on your way" <<endl; 
}

bool greedy_tile::take_money()
{
    //place holder for accessing player
    player.money = player.money/2;
    is_resolved=1;
    return 1; 
}
void jackpot::greeting()
{
     cout<<"Someone who came before you dropped their bag of money" <<endl;
     cout<<"Congrats! This is a big break. You double your money!" <<endl; 
}

bool jackpot::give_money()
{
    //place holder for accessing player
    player.money = player.money*2;
    is_resolved=1;
    return 1; 
}

void nap::greeting()
{
     cout<<"Is that a hammock?" <<endl;
     cout<<"Congrats! Take a power nap and boost your energy by 50%" <<endl; 
}

bool nap::take_nap()
{
    //place holder for accessing player
    player.energy = player.energy/2 + player.engergy;
    is_resolved=1;
    return 1; 
}

void dehydration::greeting()
{
     cout<<"You've been walking for a while" <<endl;
     cout<<"The elements are getting to you. Dehydration costs you half of your energy" <<endl; 
}

bool dehydration::dehydrate()
{
    //place holder for accessing player
    player.energy = player.energy/2;
    is_resolved=1;
    return 1; 
}
