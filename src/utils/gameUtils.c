#include <math.h>
#include <utils/gameUtils.h>

float AngleToMouseFromEntity(Entity* entity)
{
    Vector2 mousePos = GetMousePosition();

    Vector2 dir = {mousePos.x - entity->pos.x, mousePos.y - entity->pos.y};

    // atan2 returns the angle between the X‑axis and the vector
    return RAD2DEG * atan2f(dir.y, dir.x) + 90;
}
