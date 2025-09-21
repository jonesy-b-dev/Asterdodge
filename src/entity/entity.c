#include "entity.h"
#include "raylib.h"
#include <stdbool.h>
#include <string.h>

void SetEntityTexture(Entity* entitiy, const char* filename)
{
    entitiy->sprite = LoadTexture(filename);
}

void RenderEntityFloat(Entity* entity, float scale)
{
    RenderEntity(entity, (Vector2){scale, scale});
}

void RenderEntity(Entity* entity, Vector2 scale)
{
    entity->srcRec = (Rectangle){.x = 0,
                                 .y = 0,
                                 .width = (float)entity->sprite.width,
                                 .height = (float)entity->sprite.height};

    entity->dstRec = (Rectangle){.x = entity->pos.x,
                                 .y = entity->pos.y,

                                 .width = entity->srcRec.width * scale.x,
                                 .height = entity->srcRec.height * scale.y};

    // Wacky fix for collision boxes being offset, hate the solution but it works:(
    if (entity && entity->name)
    {
        /* Build the collision box using the selected divisor */
        entity->collisionBox = (Rectangle){.x = entity->dstRec.x - entity->sprite.width / (2 / scale.x),
                                           .y = entity->dstRec.y - entity->sprite.height / (2 / scale.y),
                                           .width = entity->dstRec.width,
                                           .height = entity->dstRec.height};
    }
    else
    {
        entity->collisionBox = (Rectangle){.x = 0, .y = 0, .width = 0, .height = 0};
    }

    // Vector2 origin = {0, 0};
    Vector2 origin = {entity->dstRec.width / 2.0f, entity->dstRec.height / 2.0f};

    DrawTexturePro(entity->sprite,
                   entity->srcRec,
                   entity->dstRec,
                   origin,
                   entity->angle, //+ 90,
                   WHITE);

    // DrawRectangleLinesEx(entity->collisionBox, 3.0f, RED);
    // DrawRectangleLinesEx(entity->dstRec, 2.0f, GREEN);
}
