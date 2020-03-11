#ifndef FRUPALGAME_SRC_START_MSG_HPP_INCLUDED
#define FRUPALGAME_SRC_START_MSG_HPP_INCLUDED

#include "event.hpp"

class Start_msg : public Event {
public:
	void greeting();
	void react_to_player();
	~Start_msg() override;
};

#endif // FRUPALGAME_SRC_START_MSG_HPP_INCLUDED
