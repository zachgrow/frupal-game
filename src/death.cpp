
#include "death.hpp"

Death_event::Death_event(bool is_mud)
{
	is_mud_ = is_mud;
}

void Death_event::greeting()
{
	if (is_mud_) {
		writeMsg("As you walk through the mud, your boot gets stuck.");
		writeMsg("As you try to pull your boot out, you realize you have began to sink!");
		writeMsg("You scream for help to no avail as you slowly sink below the surface.");
		writeMsg("Later, another adventurer finds a bag of supplies in this swamp...");
	} else {
		writeMsg("As you walk along, you begin to shake.");
		writeMsg("You realize your blood sugar is low!");
		writeMsg("Guess it's time to go home, we can search more tomorrow.");
	}
}

void Death_event::react_to_player()
{
	greeting();
}

Death_event::~Death_event() = default;
