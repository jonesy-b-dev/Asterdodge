#pragma once
#include "../entity/entity.h"
#include "../player/player.h"
#include <utils/gameUtils.h>

typedef struct
{
    Entity base;
    Vector2 defaultLocation;
    float speed;
    int goToPlayer;
} Asteroid;

extern Asteroid* asteroidPool;

// Fills in the asteroid pool
Asteroid* InitializeAsteroids(int asteroidAmount);

// Moves asteroids from non active to the active pool
int SpawnAsteroids(GameOptions options, Player* player);

int MoveAsteroidTowardsPlayer(Asteroid* asteroid, Player* player);

void MoveAsteroid(Asteroid* asteroid);

void AsteroidDeath(int asteroidIndex);

// Clears the pool arrays
void CleanAsteroids();
