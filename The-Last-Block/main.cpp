#include "Game.h"
using namespace sf;

int main() {

	// Init srand (Random)
	srand(static_cast<unsigned>(time(NULL)));

	// Init game engine
	Game game;


	// Game Loop
	while (game.running()) {
		// Update
		game.update();

		// Render
		game.render(); // clear old frame  
	}

	// End of Application
	return 0;
}