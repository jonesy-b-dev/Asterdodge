#include <game/game.h>

int main()
{
    GameOptions options = {.resourceDirectory = "resources",
                           .windowName = "Asterdodge",
                           .windowHeight = 600,
                           .windowWidth = 1000,
			   .asteroidPoolSize = 100};
    InitGame(options);

    RunGame(options);

    return 0;
}
