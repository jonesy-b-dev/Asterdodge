#include "entity.h"

void SetEntityTexture(Entity* entitiy, const char* filename)
{
	entitiy->sprite = LoadTexture("wabbit_alpha.png");
}

void RenderEntity(Entity entity)
{
	// draw our texture to the screen
	DrawTexture(entity.sprite, entity.pos.x, entity.pos.y, WHITE);
}
