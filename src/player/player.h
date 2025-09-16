#pragma once
#include <entity/entity.h>

typedef struct
{
    Entity base;
    float health;
    int speed;
} Player;

void RotatePlayerToMouse(Player *player);
void PlayerMove(Player *player);
