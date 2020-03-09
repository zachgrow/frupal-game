
#include "victory.hpp"

void Victory::greeting()
{
	writeMsg("OWW! You've stubbed your toe on a rock!");
	writeMsg("Hey, that rock is kinda shiny?");
	writeMsg("Wait a minute...");
	writeMsg("You did it! You found the jewel of Frupal!");
}

void Victory::react_to_player()
{
	greeting();
	player->addJewel();
}

Victory::~Victory() = default;
