#include "raylib.h"
#include <math.h>
#include <player/player.h>
#include <stdio.h>

void RotatePlayerToMouse(Player* player)
{
    if (player->isDead)
        return;

    Vector2 mousePos = GetMousePosition();

    // Vector from player to mouse
    float halfWidth = player->base.sprite.width / 2.0f;
    float halfHeight = player->base.sprite.height / 2.0f;

    Vector2 dir = {mousePos.x - player->base.pos.x + halfWidth,
                   mousePos.y - player->base.pos.y + halfHeight};

    // atan2 returns the angle (in radians) between the X‑axis and the vector
    player->base.angle = atan2f(dir.y, dir.x);
}

void PlayerMove(Player* player)
{
    if (player->isDead)
        return;

    if (IsKeyDown(KEY_D))
        player->base.pos.x += player->speed * GetFrameTime();
    if (IsKeyDown(KEY_A))
        player->base.pos.x -= player->speed * GetFrameTime();
    if (IsKeyDown(KEY_W))
        player->base.pos.y -= player->speed * GetFrameTime();
    if (IsKeyDown(KEY_S))
        player->base.pos.y += player->speed * GetFrameTime();
}

void PlayerTakeDamage(Player* player, float damage)
{
    player->health -= damage;
    printf("Player health: %f \n", player->health);
    if (player->health <= 0)
        player->isDead = true;
}
