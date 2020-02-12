#include "player.hpp"

using namespace std;
class Event
{
public:
    void greeting();
    bool react_to_player();
    bool is_active;


private:
    Pos position;
    bool is_resolved;
    bool check_conditions();
    void perform_outcome();
};

class back_track: public Event
{
    public:
        bool move_player();
};

class binoculars: public Event 
{
    public:
        bool give_binoculars();
};

class greedy_tile: public Event
{
    public:
        bool take_money();
};

class jackpot: public Event
{
    public:
        bool give_money();
};

class nap: public Event
{
    public:
        bool take_nap();
};

class dehydration: public Event
{
    public:
        bool dehydrate();

};