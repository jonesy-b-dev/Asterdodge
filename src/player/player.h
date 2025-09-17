#pragma once
#include <entity/entity.h>
#include <stdbool.h>

typedef struct
{
    Entity base;
    float health;
    int speed;
    bool isDead;
} Player;

void RotatePlayerToMouse(Player* player);
void PlayerMove(Player* player);
void PlayerTakeDamage(Player* player, float damage);
