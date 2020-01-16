
#include "gui.hpp"
#include "tile.hpp"
#include "interface.hpp"
#include <cstdio>
#include <vector>

struct Game {

	Game() noexcept;

	void loop();

};

int main(int argc, char** argv)
{
	// Read argv for json config file
	// Flags for map size?
}

Game::Game() noexcept
{
}

void Game::loop()
{
	// Fetch player action
	// Perform action
	// Write result
}

