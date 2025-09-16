#include "entity.h"
#include "raylib.h"
#include <string.h>

void SetEntityTexture(Entity* entitiy, const char* filename)
{
    entitiy->sprite = LoadTexture("wabbit_alpha.png");
}

void RenderEntity(Entity* entity, float scale)
{
    if (!entity->active)
        return;
    if (strcmp(entity->name, "Asteroid") == 0)
    {
        int x = 5;
    }

    Rectangle srcRec = {.x = 0,
                        .y = 0,
                        .width = (float)entity->sprite.width,
                        .height = (float)entity->sprite.height};

    Rectangle dstRec = {.x      = entity->pos.x - (srcRec.width  * scale) / 2.0f,
        				.y      = entity->pos.y - (srcRec.height * scale) / 2.0f,
        				.width  = srcRec.width  * scale,
        				.height = srcRec.height * scale
    };

    Vector2 origin = {
        dstRec.width  / 2.0f,
        dstRec.height / 2.0f
    };

    DrawTexturePro(entity->sprite, srcRec, dstRec, origin,
                   RAD2DEG * entity->angle + 90, WHITE);
}
