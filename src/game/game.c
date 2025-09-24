#include <game/game.h>
#include <raylib.h>
#include <resource_dir.h>
#include <stdio.h>
#include <stdlib.h>

Player player; // TODO better initialzation
UiElement healthBackGround;
UiElement healthForeGround;
GameOptions m_options;

void CheckCollisions();
void RenderEntities();
void RenderUserInterface();

int InitGame(GameOptions* options)
{
    m_options = *options;
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

    InitWindow(m_options.windowWidth, m_options.windowHeight, m_options.windowName);

    if (!SearchAndSetResourceDir(m_options.resourceDirectory))
    {
        return false;
    };

    // Setup player
    SetEntityTexture(&player.base, "wabbit_alpha.png");
    player.base.pos = (Vector2){m_options.windowWidth / 2.0f, m_options.windowHeight / 2.0f};
    player.base.active = true;
    player.base.name = "Player";
    player.speed = 100;
    player.health = 100;
    player.isDead = false;
    player.score = 0;

    // Setup entity pools
    InitializeAsteroids(m_options.asteroidPoolSize);
    InitializeBullets(m_options.bulletPoolSize);

    // Setup ui
    healthBackGround.base.pos = (Vector2){140, 50};
    healthForeGround.base.pos = (Vector2){140, 50};
    healthForeGround.base.scale = (Vector2){1, 1};
    SetEntityTexture(&healthForeGround.base, "HealthProgressBar.png");
    SetEntityTexture(&healthBackGround.base, "HealthBackGroundBar.png");

    return true;
}

int RunGame()
{
    // game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();

        // Setup the back buffer for drawing (clear color and depth buffers)
        ClearBackground(BLACK);

        SpawnAsteroids(m_options, &player);

        RotatePlayerToMouse(&player);

        PlayerMove(&player);

        for (int i = 0; i < m_options.asteroidPoolSize; i++)
        {
            if (asteroidPool[i].goToPlayer)
            {
                MoveAsteroidTowardsPlayer(&asteroidPool[i], &player);
            }
            else
            {
                MoveAsteroid(&asteroidPool[i]);
                // TODO figure out something for this
                // if (IsEntityOutOfBounds(&asteroidPool[i].base, m_options))
                //{
                //     printf("Asteroid out of bounds despawn\n");
                //     AsteroidDeath(i);
                // }
            }
        }

        for (int i = 0; i < m_options.bulletPoolSize; i++)
        {
            MoveBullet(&bulletPool[i]);
            if (IsEntityOutOfBounds(&bulletPool[i].base, m_options))
            {
                printf("Bullet out of bounds despawn\n");
                BulletDeath(i);
            }
        }

        CheckCollisions();

        RenderEntities();

        RenderUserInterface();

        EndDrawing();
    }

    ShutdownGame();
    return true;
}

void CheckCollisions()
{
    ///
    /// Collisions
    ///

    // ASTEROID -> PLAYER
    for (int i = 0; i < m_options.asteroidPoolSize; i++)
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
    for (int i = 0; i < m_options.bulletPoolSize; i++)
    {
        if (!bulletPool[i].base.active)
            continue;

        for (int x = 0; x < m_options.asteroidPoolSize; x++)
        {
            if (!asteroidPool[x].base.active)
                continue;

            if (CheckCollisionRecs(bulletPool[i].base.collisionBox,
                                   asteroidPool[x].base.collisionBox))
            {
                printf("Bullet hit asteroid\n");
                player.score += 10;
                AsteroidDeath(x);
                BulletDeath(i);
            }
        }
    }
}

void RenderEntities()
{
    // Entities
    RenderEntityFloat(&player.base, 1.2);
    // ASTEROID
    for (int i = 0; i < m_options.asteroidPoolSize; i++)
    {
        RenderEntityFloat(&asteroidPool[i].base, 0.5);
    }
    // BULLET
    for (int i = 0; i < m_options.bulletPoolSize; i++)
    {
        RenderEntityFloat(&bulletPool[i].base, 0.05);
    }
}

void RenderUserInterface()
{
    // UI
    RenderEntityFloat(&healthBackGround.base, 1);
    RenderEntity(&healthForeGround.base, healthForeGround.base.scale);
    DrawText("HP", 15, 40, 20, WHITE);

    char scorebuffer[30];
    snprintf(scorebuffer, sizeof(scorebuffer), "Score: %d", player.score);
    DrawText(scorebuffer, m_options.windowWidth - 200, 40, 20, WHITE);
}

int ShutdownGame()
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
