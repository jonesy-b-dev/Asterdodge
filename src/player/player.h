#pragma once
#include <entity/entity.h>
#include <stdbool.h>
#include <uiElement/uiElement.h>

typedef struct
{
    Entity base;
    int health;
    int speed;
    bool isDead;
} Player;

void RotatePlayerToMouse(Player* player);
void PlayerMove(Player* player);
void PlayerTakeDamage(Player* player, int damage, UiElement* healthBar);
