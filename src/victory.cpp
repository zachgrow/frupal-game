
#include "victory.hpp"

void Victory::greeting()
{
	writeMsg("OWW! You've stubbed your toe on a rock!\n"
		"Hey, that rock is kinda shiny?\n"
		"Wait a minute...\n"
		"You did it! You found the jewel of Frupal!\n");
}

void Victory::react_to_player()
{
	greeting();
	player->addJewel();
}
