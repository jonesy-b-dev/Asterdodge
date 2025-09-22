#include <bullet/bullet.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

Bullet* bulletPool = NULL;
int m_bulletAmount;

Bullet* InitializeBullets(int bulletAmount)
{
    m_bulletAmount = bulletAmount;
    bulletPool = (Bullet*)malloc(bulletAmount * sizeof(Bullet));
    if (!bulletPool)
    {
        perror("Failed to allocate bullet pool");
        return NULL;
    }

    Texture2D bulletSprite = LoadTexture("Bullet.png");

    for (int i = 0; i < bulletAmount; i++)
    {
        bulletPool[i].base.active = false;
        bulletPool[i].defaultLocation = (Vector2){-80000.0f, 10000.0f};
        bulletPool[i].base.pos = bulletPool[i].defaultLocation;
        bulletPool[i].base.sprite = bulletSprite;
        bulletPool[i].base.angle = 0;
        bulletPool[i].base.name = "Bullet";
    }

    return bulletPool;
}

int ShootBullet(Player* player)
{
    printf("Player Schooting\n");
    int foundNonActive = false;
    for (int i = 0; i < m_bulletAmount; i++)
    {
        if (bulletPool[i].base.active == false)
        {
            foundNonActive = true;
            bulletPool[i].base.active = true;
            bulletPool[i].base.pos = player->base.pos;
            bulletPool[i].base.angle = AngleToMouseFromEntity(&bulletPool[i].base);
            bulletPool[i].speed = 200;
            break;
        }
    }
    if (foundNonActive == false)
    {
        perror("Found no non active bullet, increase the pool! \n");
        return false;
    }
    return true;
}

void MoveBullet(Bullet* bullet)
{
    float bulletRadians = DEG2RAD * (bullet->base.angle + 90);

    bullet->base.pos.x -= bullet->speed * cosf(bulletRadians) * GetFrameTime();
    bullet->base.pos.y -= bullet->speed * sinf(bulletRadians) * GetFrameTime();
}
