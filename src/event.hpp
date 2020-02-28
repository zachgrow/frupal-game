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

class Back_Track : public Event
{
    public:
        void greeting();
        bool move_player();
    private:
        Pos position;
};

class Wind_Storm : public Event
{
    public:
        void greeting();
        bool move_player();
    private:
        Pos position;
};

class Binoculars : public Event
{
    public:
        void greeting();
        bool give_binoculars();
    private:
        Pos position;
};

class Greedy_Tile: public Event
{
    public:
        void greeting();
        bool take_money();
    private:
        Pos position;
};

class Jackpot : public Event
{
    public:
        void greeting();
        bool give_money();
    private:
        Pos position;
};

class Nap : public Event
{
    public:
        void greeting();
        bool take_nap();
    private:
        Pos position;
};

class Dehydration : public Event
{
    public:
        void greeting();
        bool dehydrate();
    private:
        Pos position;

};

class Troll : public Event
{
    public:
        void greeting();
        bool steal_money();
        bool labor();
    private:
        Pos position;
};

class Mud_Event : public Event
{
    public:
        void greeting();
        bool mud_boots();
    private:
        Pos position;

};

class Tree_Event : public Event
{
    public:
        void greeting();
        bool chop();
    private:
        Pos position;

};

class Rock_Event : public Event
{
    public:
        void greeting();
        bool mud();
    private:
        Pos position;

};

class Quicksand_Event : public Event
{
    public:
        void greeting();
        bool quicksand();
    private:
        Pos position;

};

class Water_Event : public Event
{
    public:
        void greeting();
        bool boating();
    private:
        Pos position;

};

#endif
