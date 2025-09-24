#include <math.h>
#include <stdio.h>
#include <utils/gameUtils.h>

float AngleToMouseFromEntity(Entity* entity)
{
    Vector2 mousePos = GetMousePosition();

    Vector2 dir = {mousePos.x - entity->pos.x, mousePos.y - entity->pos.y};

    // atan2 returns the angle between the X‑axis and the vector
    return RAD2DEG * atan2f(dir.y, dir.x) + 90;
}

bool IsEntityOutOfBounds(Entity* entity, GameOptions options)
{
	if ((entity->pos.x < -100 || entity->pos.x > options.windowWidth) && entity->active)
	{
		return true;
	}
	if ((entity->pos.y < -100 || entity->pos.y > options.windowHeight) && entity->active)
	{
		return true;
	}
	return false;
}
