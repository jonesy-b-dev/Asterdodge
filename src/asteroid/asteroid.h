#pragma once
#include <entity/entity.h>
#include <utils/gameUtils.h>

typedef struct
{
    Entity base;
    Vector2 defaultLocation;
} Asteroid;

extern Asteroid *asteroidPool;

// Fills in the asteroid pool
Asteroid *InitializeAsteroids(int asteroidAmount);

// Moves asteroids from non active to the active pool
int SpawnAsteroids(GameOptions options);

void AsteroidDeath();

// Clears the pool arrays
void CleanAsteroids();
