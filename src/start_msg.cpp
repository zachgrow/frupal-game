
#include "start_msg.hpp"

void Start_msg::greeting()
{
	writeMsg("Welcome to the island of Frupal!");
	writeMsg("Here the mad monk Frupal hid the magical gemstones of Frupal.");
	writeMsg("Now can you Jane Frupal find the magical Frupal to frupal frupal Frupal?");
}

void Start_msg::react_to_player()
{
	greeting();
}

Start_msg::~Start_msg() = default;
