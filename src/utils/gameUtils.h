#pragma once
#include <entity/entity.h>

typedef struct
{
    int windowWidth;
    int windowHeight;
    const char* windowName;
    const char* resourceDirectory;
    int asteroidPoolSize;
    int bulletPoolSize;
} GameOptions;

float AngleToMouseFromEntity(Entity* entity);
