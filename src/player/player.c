#include "raylib.h"
#include <math.h>
#include <player/player.h>

void RotatePlayerToMouse(Player *player)
{
    Vector2 mousePos = GetMousePosition();

    // Vector from player to mouse
    float halfWidth = player->base.sprite.width / 2.0f;
    float halfHeight = player->base.sprite.height / 2.0f;

    Vector2 dir = {mousePos.x - player->base.pos.x + halfWidth,
                   mousePos.y - player->base.pos.y + halfHeight};

    // atan2 returns the angle (in radians) between the X‑axis and the vector
    player->base.angle = atan2f(dir.y, dir.x);
}

void PlayerMove(Player *player)
{
    if (IsKeyDown(KEY_D))
        player->base.pos.x += 2.0f;
    if (IsKeyDown(KEY_A))
        player->base.pos.x -= 2.0f;
    if (IsKeyDown(KEY_W))
        player->base.pos.y -= 2.0f;
    if (IsKeyDown(KEY_S))
        player->base.pos.y += 2.0f;
    if (IsKeyPressed(KEY_P))
        player->base.active = !player->base.active;
}
