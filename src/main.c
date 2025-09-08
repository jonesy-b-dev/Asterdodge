#include "game/game.h"
#include "utils.h"

int main ()
{
	GameOptions options = { 
		.resourceDirectory = "resources",
		.windowName = "Asterdodge",
		.windowHeight = 600,
		.windowWidth = 1000
	};

	InitGame(options);
	
	RunGame();	

	return 0;
}
