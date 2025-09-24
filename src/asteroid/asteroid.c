#include "asteroid.h"
#include "raylib.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils/gameUtils.h>

Asteroid* asteroidPool = NULL;
float spawnTimerTarget = 0;
float spawnTimer = 0;
float difficultyIncreaseInterval = 5;
float difficultyIncreaseTime = 0;
int m_asteroidAmount = 0;

Asteroid* InitializeAsteroids(int asteroidAmount)
{
    spawnTimerTarget = 5 + ((float)GetRandomValue(100, 1000) / 1000.0f);
    printf("%f", spawnTimerTarget);

    m_asteroidAmount = asteroidAmount;
    asteroidPool = (Asteroid*)malloc(asteroidAmount * sizeof(Asteroid));

    if (!asteroidPool)
    {
        perror("Failed to allocate asteroid pool");
        return NULL;
    }

    Texture2D asteroidSprite = LoadTexture("Asteroid.png");

    for (int i = 0; i < asteroidAmount; i++)
    {
        asteroidPool[i].base.active = false;
        asteroidPool[i].defaultLocation = (Vector2){10000.0f, 10000.0f};
        asteroidPool[i].base.pos = asteroidPool[i].defaultLocation;
        asteroidPool[i].base.sprite = asteroidSprite;
        asteroidPool[i].base.name = "Asteroid";
        asteroidPool[i].goToPlayer = 0;
    }

    return asteroidPool;
}

Vector2 CalculateSpawnLocation(GameOptions options)
{
    // This value is the side of the screen the asteroid will spawn in
    // 1 = top
    // 2 = bottom
    // 3 = left
    // 4 = right
    int screenSide = GetRandomValue(1, 4);

    switch (screenSide)
    {
    case 1:
        return (Vector2){GetRandomValue(0, options.windowWidth), GetRandomValue(-300, 0)};
        break;
    case 2:
        return (Vector2){GetRandomValue(0, options.windowWidth),
                         GetRandomValue(options.windowHeight + 300, options.windowHeight)};
        break;
    case 3:
        return (Vector2){GetRandomValue(-300, 0), GetRandomValue(0, options.windowHeight)};
        break;
    case 4:
        return (Vector2){GetRandomValue(options.windowWidth + 300, options.windowWidth),
                         GetRandomValue(0, options.windowHeight)};
        break;
    default:
        return (Vector2){options.windowWidth / 2.0f, options.windowHeight / 2.0f};
        perror("Somehow failed to generate number between 1 and 4\n");
        break;
    }
}

int SpawnAsteroids(GameOptions options, Player* player)
{
    printf("%f\n", spawnTimerTarget);
    spawnTimer += GetFrameTime();
    difficultyIncreaseTime += GetFrameTime();

    // Decrease spawnTimerTarget every 5 seconds
    if (difficultyIncreaseTime >= difficultyIncreaseInterval)
    {
        difficultyIncreaseTime = 0;
        float scale = 0.95f + ((float)GetRandomValue(0, 500) / 10000.0f);
        spawnTimerTarget *= scale;

        if (spawnTimerTarget < 0.5f)
        {
            spawnTimerTarget = 0.5f;
        }
    }

    if (spawnTimer >= spawnTimerTarget)
    {
        spawnTimer = 0;
        printf("SpawnAsteroid\n");

        // Get first non active asteroid
        int foundNonActive = false;
        for (int i = 0; i < m_asteroidAmount; i++)
        {
            if (asteroidPool[i].base.active == false)
            {
                foundNonActive = true;
                asteroidPool[i].base.active = true;
                Vector2 spawnPosition = CalculateSpawnLocation(options);
                printf("Spawn Location: x: ");
                printf("%f", spawnPosition.x);
                printf("\n y: ");
                printf("%f", spawnPosition.y);

                asteroidPool[i].base.pos = spawnPosition;
                asteroidPool[i].speed = 100;
                asteroidPool[i].base.angle =
                    RAD2DEG * atan2f(player->base.pos.x - asteroidPool[i].base.pos.x,
                                     player->base.pos.y - asteroidPool[i].base.pos.y);
                asteroidPool[i].goToPlayer = GetRandomValue(0, 1);
                printf("\nAsteroid spawned on screen\n");
                printf("%i\n", asteroidPool[i].goToPlayer);
                break;
            }
        }
        if (foundNonActive == false)
        {
            perror("Found no non active asteroid, increase the pool! \n");
            return false;
        }
    }
    return true;
}

int MoveAsteroidTowardsPlayer(Asteroid* asteroid, Player* player)
{
    if (asteroid->base.active == true)
    {
        Vector2 dir = {player->base.pos.x - asteroid->base.pos.x,
                       player->base.pos.y - asteroid->base.pos.y};

        float distance = sqrtf(dir.x * dir.x + dir.y * dir.y);

        if (distance > 0.0f)
        {
            dir.x /= distance;
            dir.y /= distance;

            float step = asteroid->speed * GetFrameTime();
            if (step > distance)
                step = distance; // stop exactly at player

            asteroid->base.pos.x += dir.x * step;
            asteroid->base.pos.y += dir.y * step;
        }
    }
    return true;
}

void MoveAsteroid(Asteroid* asteroid)
{
    float asteroidRadians = DEG2RAD * (asteroid->base.angle - 90);

    asteroid->base.pos.x -= asteroid->speed * cosf(asteroidRadians) * GetFrameTime();
    asteroid->base.pos.y -= asteroid->speed * sinf(asteroidRadians) * GetFrameTime();
}

void AsteroidDeath(int asteroidIndex)
{
    asteroidPool[asteroidIndex].base.pos = asteroidPool[asteroidIndex].defaultLocation;
    asteroidPool[asteroidIndex].base.active = false;
}
