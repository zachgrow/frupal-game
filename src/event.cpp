#include "event.hpp"

Event::Event()
{
	is_active=0;
    is_resolved=0;
}

void Event::greeting(){
    cout<<"Uh-Oh You've run into a little trouble " <<endl;
}
bool Event::react_to_player(){
    cout<<"Would you like to proceede with this challenge? (Y/N) "<<endl;
	char response;	
	cin>>response;
	response=toupper(response);
    
    if (response=='N')
    {
        return 0;
    }
    else
    {
        return 1;
    }
    
}


