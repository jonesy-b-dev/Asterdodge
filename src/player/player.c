#include "raylib.h"
#include <bullet/bullet.h>
#include <player/player.h>
#include <stdio.h>

void RotatePlayerToMouse(Player* player)
{
    if (player->isDead)
        return;

    player->base.angle = AngleToMouseFromEntity(&player->base);
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
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_SPACE))
    {
        ShootBullet(player);
    }
}

void PlayerTakeDamage(Player* player, int damage, UiElement* healthBar)
{
    printf("Damage %i: \n", damage);
    player->health -= damage;
    if (player->health <= 0)
    {
        player->isDead = true;
        healthBar->base.scale.x = 0;
    }

    healthBar->base.scale.x = (float)player->health / 100.0f;

    printf("Player health: %f \n", player->health);
}
