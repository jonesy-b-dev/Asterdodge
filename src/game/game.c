#include "game.h"
#include "raylib.h"
#include "../../include/resource_dir.h"	// utility header for SearchAndSetResourceDir

// Load a texture from the resources directory
Texture wabbit;

int InitGame(GameOptions options)
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(options.windowWidth, options.windowHeight, options.windowName);

	if(!SearchAndSetResourceDir(options.resourceDirectory))
	{
		return false;
	};
	// Load a texture from the resources directory
	wabbit = LoadTexture("wabbit_alpha.png");
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

		// draw some text using the default font
		DrawText("Hello Raylib", 200,200,20,WHITE);

		// draw our texture to the screen
		DrawTexture(wabbit, 400, 200, WHITE);
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	ShutdownGame();
	return true;
}

int ShutdownGame()
{
	// cleanup
	UnloadTexture(wabbit);

	CloseWindow();
	return true;
}
