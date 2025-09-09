#include <player/player.h>
#include <math.h>
#include <stdio.h>

void RotatePlayerToMouse(Player* player){

	// Get mouse coordinates (screen space)
	Vector2 mousePos = GetMousePosition();

	// Vector from player to mouse
	Vector2 dir = { mousePos.x - player->base.pos.x,
					mousePos.y - player->base.pos.y };

	// atan2 returns the angle (in radians) between the X‑axis and the vector
	player->base.angle = atan2f(dir.y, dir.x);
}
