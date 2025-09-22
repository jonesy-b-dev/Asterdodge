#include <game/game.h>
#include <raylib.h>
#include <resource_dir.h>
#include <stdio.h>
#include <stdlib.h>

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

    // Setup entity pools
    InitializeAsteroids(options.asteroidPoolSize);
    InitializeBullets(options.bulletPoolSize);

    // Setup ui
    healthBackGround.base.pos = (Vector2){140, 50};
    healthForeGround.base.pos = (Vector2){140, 50};
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

        for (int i = 0; i < options.bulletPoolSize; i++)
        {
            MoveBullet(&bulletPool[i]);
        }
        ///
        /// Collisions
        ///

        // ASTEROID -> PLAYER
        for (int i = 0; i < options.asteroidPoolSize; i++)
        {
            if (CheckCollisionRecs(asteroidPool[i].base.collisionBox, player.base.collisionBox))
            {
                printf("Hit player\n");
                AsteroidDeath(i);
                if (!player.isDead)
                {
                    PlayerTakeDamage(&player, 10, &healthForeGround);
                }
            }
        }

        // BULLET -> ASTEROID
        for (int i = 0; i < options.bulletPoolSize; i++)
        {
            if (!bulletPool[i].base.active)
                continue;

            for (int x = 0; x < options.asteroidPoolSize; x++)
            {
                if (!asteroidPool[x].base.active)
                    continue;

                if (CheckCollisionRecs(bulletPool[i].base.collisionBox,
                                       asteroidPool[x].base.collisionBox))
                {
                    printf("Bullet hit asteroid\n");
                    AsteroidDeath(x);
                }
            }
        }
        ///
        /// RENDERING
        ///

        // Entities
        RenderEntityFloat(&player.base, 1.2);
        // ASTEROID
        for (int i = 0; i < options.asteroidPoolSize; i++)
        {
            if (!asteroidPool[i].base.active)
                continue;
            RenderEntityFloat(&asteroidPool[i].base, 0.5);
        }
        // BULLET
        for (int i = 0; i < options.bulletPoolSize; i++)
        {
            if (!bulletPool[i].base.active)
                continue;
            RenderEntityFloat(&bulletPool[i].base, 0.1);
        }

        // UI
        RenderEntityFloat(&healthBackGround.base, 1);
        RenderEntity(&healthForeGround.base, healthForeGround.base.scale);
        DrawText("HP", 100, 100, 20, WHITE); // Draw text (using default font)
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
    UnloadTexture(bulletPool[1].base.sprite);
    free(asteroidPool);
    free(bulletPool);

    CloseWindow();
    return true;
}
