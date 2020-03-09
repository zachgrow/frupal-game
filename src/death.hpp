
#ifndef FRUPALGAME_SRC_DEATH_HPP_INCLUDED
#define FRUPALGAME_SRC_DEATH_HPP_INCLUDED

#include "event.hpp"

class Death_event : public Event {
	bool is_mud_;
public:
	Death_event(bool is_mud);
	void greeting();
	void react_to_player();
	~Death_event() override;
};

#endif // FRUPALGAME_SRC_DEATH_HPP_INCLUDED
