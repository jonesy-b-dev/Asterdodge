#include "game.h"
#include "raylib.h"
#include <resource_dir.h>
#include <player/player.h>
#include <entity/entity.h>

Player player;

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
	player.base.pos = (Vector2){200, 200};

	return true;
}

int RunGame()
{
	// game loop
	while (!WindowShouldClose())		
	{
		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		RotatePlayerToMouse(&player);
		RenderEntity(player.base);

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
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
