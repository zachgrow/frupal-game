
#include "death.hpp"

Death_event::Death_event(bool is_mud)
{
	is_mud_ = is_mud;
}

void Death_event::greeting()
{
	if (is_mud_)
		writeMsg("As you walk through the mud, your boot get's stuck.\n"
				 "As you try to pull your boot out, you realize you have began to sink!\n"
				 "You futilly scream for help as you slow sink below the surface.\n"
				 "Later, another adventure finds a bag of supplies in this swamp...\n");
	else
		writeMsg("As you walk along, you begun to shake.\n"
				 "You realize your blood suger is low!\n"
				 "Guess its time to go home, we can search more tomorrow.\n");
}

void Death_event::react_to_player()
{
	greeting();
}

Death_event::~Death_event() = default;
