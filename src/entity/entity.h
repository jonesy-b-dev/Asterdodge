#pragma once
#include "raylib.h"
#include <stdbool.h>

typedef struct
{
    const char* name;
    Vector2 pos;
    Vector2 vel;
    Rectangle srcRec;
    Rectangle dstRec;
    Texture2D sprite;
    float angle;
    // float   radius;   // for simple circle collision
    bool active; // true if currently in use

} Entity;

void SetEntityTexture(Entity* entitiy, const char* filename);
void RenderEntityFloat(Entity* entitiy, float scale);
void RenderEntity(Entity* entity, Vector2 scale);
