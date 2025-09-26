#pragma once
#include <entity/entity.h>
#include <stdbool.h>

typedef struct
{
    int windowWidth;
    int windowHeight;
    const char* windowName;
    const char* resourceDirectory;
    int asteroidPoolSize;
    int bulletPoolSize;
	float startDifficulty;
	float difficulty;
} GameOptions;

float AngleToMouseFromEntity(Entity* entity);
bool IsEntityOutOfBounds(Entity* entity, GameOptions options);
