#pragma once
#include <entity/entity.h>
#include <player/player.h>
#include <utils/gameUtils.h>

typedef struct
{
    Entity base;
    Vector2 defaultLocation;
    float speed;
} Bullet;

extern Bullet* bulletPool;

// Fills in the asteroid pool
Bullet* InitializeBullets(int bulletAmount);

int ShootBullet(Player* player);

void BulletDespawn(int asteroidIndex);

void MoveBullet(Bullet* bullet);

// Clears the pool arrays
void CleanBulletPool();
