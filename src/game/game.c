#include "game.h"
#include "raylib.h"
#include <asteroid/asteroid.h>
#include <entity/entity.h>
#include <player/player.h>
#include <resource_dir.h>

Player player; // TODO better initialzation

int InitGame(GameOptions options)
{
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

    InitWindow(options.windowWidth, options.windowHeight, options.windowName);

    if (!SearchAndSetResourceDir(options.resourceDirectory))
    {
        return false;
    };

    // Setup player
    SetEntityTexture(&player.base, "wabbit_alpha.png");
    player.base.pos =
        (Vector2){options.windowWidth / 2.0f, options.windowHeight / 2.0f};
    player.base.active = true;
    player.base.name = "Player";
    player.speed = 100;

    // Setup asteroid spawner
    InitializeAsteroids(options.asteroidPoolSize);

    return true;
}

int RunGame(GameOptions options)
{
    // game loop
    while (!WindowShouldClose())
    {
        // drawing
        BeginDrawing();

        // Setup the back buffer for drawing (clear color and depth buffers)
        ClearBackground(BLACK);

        SpawnAsteroids(options);

        RotatePlayerToMouse(&player);
        PlayerMove(&player);
        RenderEntity(&player.base, 1.2);

        for (int i = 0; i < options.asteroidPoolSize; i++)
        {
            RenderEntity(&asteroidPool[i].base, 0.5);
	    MoveAsteroidTowardsPlayer(&asteroidPool[i], &player);
        }

        EndDrawing();
    }

    ShutdownGame(options);
    return true;
}

int ShutdownGame(GameOptions options)
{
    // cleanup
    UnloadTexture(player.base.sprite);
    UnloadTexture(asteroidPool[1].base.sprite);

    CloseWindow();
    return true;
}
