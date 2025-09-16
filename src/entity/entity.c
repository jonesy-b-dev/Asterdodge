#include "entity.h"
#include "raylib.h"

void SetEntityTexture(Entity *entitiy, const char *filename)
{
    entitiy->sprite = LoadTexture("wabbit_alpha.png");
}

void RenderEntity(Entity entity, float scale)
{
    if (!entity.active)
        return;

    Rectangle srcRec = {.x = 0,
                        .y = 0,
                        .width = (float)entity.sprite.width,
                        .height = (float)entity.sprite.height};

    Rectangle dstRec = {.x = entity.pos.x - srcRec.width / 2.0f,
                        .y = entity.pos.y - srcRec.height / 2.0f,
                        .width = srcRec.width * scale,
                        .height = srcRec.height * scale};

    Vector2 origin = {srcRec.width * scale / 2.0f,
                      srcRec.height * scale / 2.0f};

    // draw our texture to the screen
    // DrawTextureEx(entity.sprite, entity.pos, RAD2DEG * entity.angle, 1,
    // WHITE);
    DrawTexturePro(entity.sprite, srcRec, dstRec, origin,
                   RAD2DEG * entity.angle + 90, WHITE);
}
