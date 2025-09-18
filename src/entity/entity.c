#include "entity.h"
#include "raylib.h"
#include <stdbool.h>

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

    entity->dstRec = (Rectangle){.x = entity->pos.x - (entity->srcRec.width * scale.x) / 2.0f,
                                 .y = entity->pos.y - (entity->srcRec.height * scale.y) / 2.0f,
                                 .width = entity->srcRec.width * scale.x,

                                 .height = entity->srcRec.height * scale.x};

    Vector2 origin = {entity->dstRec.width / 2.0f, entity->dstRec.height / 2.0f};

    DrawTexturePro(entity->sprite,
                   entity->srcRec,
                   entity->dstRec,
                   origin,
                   RAD2DEG * entity->angle + 90,
                   WHITE);
}
