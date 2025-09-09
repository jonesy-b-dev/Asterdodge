#pragma once
#include <entity/entity.h>

typedef struct 
{
	Entity base;
	float health;
} Player;

void RotatePlayerToMouse(Player* player);
