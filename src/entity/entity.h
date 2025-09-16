#pragma once
#include "raylib.h"
#include <stdbool.h>

typedef struct
{
    const char* name;
    Vector2 pos;
    Vector2 vel;
    Texture2D sprite;
    float angle;
    // float   radius;   // for simple circle collision
    bool active; // true if currently in use
} Entity;

void SetEntityTexture(Entity* entitiy, const char* filename);
void RenderEntity(Entity* entitiy, float scale);
