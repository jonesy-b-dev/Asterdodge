#include "raylib.h"
#include <game/game.h>
#include <resource_dir.h>
#include <stdio.h>

Player player; // TODO better initialzation
UiElement healthBackGround;
UiElement healthForeGround;

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
    player.base.pos = (Vector2){options.windowWidth / 2.0f, options.windowHeight / 2.0f};
    player.base.active = true;
    player.base.name = "Player";
    player.speed = 100;
    player.health = 100;
    player.isDead = false;

    // Setup asteroid spawner
    InitializeAsteroids(options.asteroidPoolSize);

    // Setup ui
    healthBackGround.base.pos = (Vector2){115, 115};
    healthForeGround.base.pos = (Vector2){110, 110};
	healthForeGround.base.scale = (Vector2){1, 1};
    SetEntityTexture(&healthForeGround.base, "HealthProgressBar.png");
    SetEntityTexture(&healthBackGround.base, "HealthBackGroundBar.png");

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

        for (int i = 0; i < options.asteroidPoolSize; i++)
        {
            MoveAsteroidTowardsPlayer(&asteroidPool[i], &player);
        }

        ///
        /// Collisions
        ///
        for (int i = 0; i < options.asteroidPoolSize; i++)
        {
            if (CheckCollisionRecs(asteroidPool[i].base.collisionBox, player.base.collisionBox))
            {
                printf("Hit player\n");
                AsteroidDeath(i);
				if(!player->isDead)
				{
					PlayerTakeDamage(&player, 50, &healthForeGround);
				}
            }
        }

        ///
        /// RENDERING
        ///

		// Entities
        RenderEntityFloat(&player.base, 1.2);
        for (int i = 0; i < options.asteroidPoolSize; i++)
        {
            RenderEntityFloat(&asteroidPool[i].base, 0.5);
        }

		// UI
		RenderEntityFloat(&healthBackGround.base, 1);
		RenderEntity(&healthForeGround.base, healthForeGround.base.scale);

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
    free(asteroidPool);

    CloseWindow();
    return true;
}
