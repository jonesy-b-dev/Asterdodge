#include <game/game.h>
#include <utils/gameUtils.h>

int main()
{
    GameOptions options = {.resourceDirectory = "resources",
                           .windowName = "Asterdodge",
                           .windowHeight = 600,
                           .windowWidth = 1000,
                           .asteroidPoolSize = 100,
                           .bulletPoolSize = 100,
                           .startDifficulty = 0.75f,
						   .difficulty = 100.0f};
    InitGame(&options);

    RunGame();

    return 0;
}
