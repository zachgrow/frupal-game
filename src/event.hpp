#ifndef FRUPALGAME_SRC_EVENT_HPP_INCLUDED
#define FRUPALGAME_SRC_EVENT_HPP_INCLUDED
#include "player.hpp"
#include <iostream>

using namespace std;

class Event
{
public:
    Event();
	virtual ~Event() {}
    virtual void greeting();
    virtual void react_to_player() = 0;
    bool is_active;
    bool is_resolved;
	static Player *player;
	static void setPlayerPtr(Player *inputPlayer);
	static void (*writeMsg)(const std::string&); // the pointer to the GUI msg log
	static void setMsgLogPtr(void (*writeMsgPtr)(const std::string&));


private:
    Pos position;
    bool check_conditions();
    void perform_outcome();
};

class Back_Track : public Event
{
    public:
        void greeting();
		void react_to_player();
        bool move_player();
    private:
        Pos position;
};

class Wind_Storm : public Event
{
    public:
        void greeting();
		void react_to_player();
        bool move_player();
    private:
        Pos position;
};

class Binoculars : public Event
{
    public:
        void greeting();
		void react_to_player();
        bool give_binoculars();
    private:
        Pos position;
};

class Greedy_Tile: public Event
{
    public:
        void greeting();
		void react_to_player();
        bool take_money();
    private:
        Pos position;
};

class Jackpot : public Event
{
    public:
        void greeting();
		void react_to_player();
        bool give_money();
    private:
        Pos position;
};

class Nap : public Event
{
    public:
        void greeting();
		void react_to_player();
        bool take_nap();
    private:
        Pos position;
};

class Dehydration : public Event
{
    public:
        void greeting();
		void react_to_player();
        bool dehydrate();
    private:
        Pos position;

};

class Troll : public Event
{
    public:
        void greeting();
		void react_to_player();
        bool steal_money();
        bool labor();
    private:
        Pos position;
};

class Mud_Event : public Event
{
    public:
        void greeting();
		void react_to_player();
        bool mud_boots();
    private:
        Pos position;

};

class Tree_Event : public Event
{
    public:
        void greeting();
		void react_to_player();
        bool chop();
    private:
        Pos position;

};

class Rock_Event : public Event
{
    public:
        void greeting();
		void react_to_player();
        bool mud();
    private:
        Pos position;

};

class Quicksand_Event : public Event
{
    public:
        void greeting();
		void react_to_player();
        bool quicksand();
    private:
        Pos position;

};

class Water_Event : public Event
{
    public:
        void greeting();
		void react_to_player();
        bool boating();
    private:
        Pos position;

};

#endif
