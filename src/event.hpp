#ifndef FRUPALGAME_SRC_EVENT_HPP_INCLUDED
#define FRUPALGAME_SRC_EVENT_HPP_INCLUDED
#include "player.hpp"
#include <iostream>

using namespace std;

class Event
{
public:
    Event();
    virtual void greeting();
    virtual void react_to_player();
    bool is_active;
    bool is_resolved;



private:
    Pos position;
    bool check_conditions();
    void perform_outcome();
};

class back_track : public Event
{
    public:
        void greeting();
        bool move_player();
    private:
        Pos position;
};

class wind_storm : public Event
{
    public:
        void greeting();
        bool move_player();
    private:
        Pos position;
};

class binoculars : public Event 
{
    public:
        void greeting();
        bool give_binoculars();
    private:
        Pos position;
};

class greedy_tile: public Event
{
    public:
        void greeting();
        bool take_money();
    private:
        Pos position;
};

class jackpot : public Event
{
    public:
        void greeting();
        bool give_money();
    private:
        Pos position;
};

class nap : public Event
{
    public:
        void greeting();
        bool take_nap();
    private:
        Pos position;
};

class dehydration : public Event
{
    public:
        void greeting();
        bool dehydrate();
    private:
        Pos position;

};

class troll : public Event
{
    public:
        void greeting();
        bool steal_money();
        bool labor();
    private:
        Pos position;
};

#endif