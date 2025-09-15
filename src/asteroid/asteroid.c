#include "asteroid.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <utils/gameUtils.h>

Asteroid *asteroidPool = NULL;
float maxNumberForSpawn = 1000;
int m_asteroidAmount;

Asteroid *InitializeAsteroids(int asteroidAmount)
{
    m_asteroidAmount = asteroidAmount;
    asteroidPool = (Asteroid *)malloc(asteroidAmount * sizeof(Asteroid));
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
    }

    return asteroidPool;
}

int SpawnAsteroids(GameOptions options)
{
    int result = GetRandomValue(1, 1000);
    if (GetRandomValue(100, 1000) >= maxNumberForSpawn)
    {
        if (maxNumberForSpawn >= 0)
            maxNumberForSpawn--;

        printf("SpawnAsteroid\n");
        printf("%f", maxNumberForSpawn);
        printf("\n");

        // Get first non active asteroid
        // for (int i = 0; i < sizeof(asteroidPool) / sizeof(Asteroid); i++)
        int foundNonActive = false;
        for (int i = 0; i < m_asteroidAmount; i++)
        {
            if (asteroidPool[i].base.active == false)
            {
                foundNonActive = true;
                asteroidPool[i].base.active = true;
                Vector2 spawnPosition = {
                    GetRandomValue(1, options.windowWidth),
                    GetRandomValue(1, options.windowHeight)};

                asteroidPool[i].base.pos = spawnPosition;
                printf("Asteroid spawned on screen\n");
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
