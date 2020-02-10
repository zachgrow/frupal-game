#ifndef FRUPALGAME_SRC_TILE_HPP_INCLUDED
#define FRUPALGAME_SRC_TILE_HPP_INCLUDED
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