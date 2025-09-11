#include "game.h"
#include "raylib.h"
#include <resource_dir.h>
#include <player/player.h>
#include <entity/entity.h>
#include <asteroid/asteroid.h>

Player player; // TODO better initialzation


int InitGame(GameOptions options)
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(options.windowWidth, options.windowHeight, options.windowName);

	if(!SearchAndSetResourceDir(options.resourceDirectory))
	{
		return false;
	};

	// Setup player
	SetEntityTexture(&player.base, "wabbit_alpha.png");
	player.base.pos = (Vector2){options.windowWidth / 2, options.windowHeight / 2};
	player.base.active = true;
	player.base.name = "Player";

	// Setup asteroid spawner
	Asteroid* asteroidPool = InitializeAsteroids(options.asteroidPoolSize);

	return true;
}

int RunGame(GameOptions options)
{
	// game loop
	while (!WindowShouldClose())		
	{
		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		SpawnAsteroids(options);

		RotatePlayerToMouse(&player);
		PlayerMove(&player);
		RenderEntity(player.base);

        for (int i = 0; i < options.asteroidPoolSize; i++)
		{
			RenderEntity(asteroidPool[i].base);
		}

		EndDrawing();
	}

	ShutdownGame();
	return true;
}

int ShutdownGame()
{
	// cleanup
	UnloadTexture(player.base.sprite);

	CloseWindow();
	return true;
}
