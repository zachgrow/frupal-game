
#ifndef FRUPALGAME_SRC_VICTORY_EVENT_HPP_INCLUDED
#define FRUPALGAME_SRC_VICTORY_EVENT_HPP_INCLUDED

#include "event.hpp"

class Victory : public Event {
    public:
        void greeting();
		void react_to_player();
};

#endif // FRUPALGAME_SRC_VICTORY_EVENT_HPP_INCLUDED
