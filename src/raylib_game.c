/*******************************************************************************************
*
*   raylib-5k-jam !
*	Andrew Hamel
*	
*	GitHub will tell you that this is generated from the raylib-game-template, but very early
*	in dev I decided against trying to use his system (which is a great learning resource)
*	for my submission and stripped it back to where I'm really only borrowing the Makefile
*	and folder structure, and even then I'm making some significant changes to the project.
*
*   This game has been created using raylib (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2022 Andrew Hamel (andrewhamel.ca)
*
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"
#include <emscripten/emscripten.h>

#include "player.h"
#include "colors.h"
#include "buttons.h"

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
// Constants
const int screenWidth = 900;
const int screenHeight = 675;

// Variable
Music music = { 0 };
float frametime = 0.0f;
player __player = {0};
Color colors[5] = { {0}, {0}, {0}, {0}, {0} };
bool mute = true;

//----------------------------------------------------------------------------------
// Resources
//----------------------------------------------------------------------------------
Music bgm[5] = { {0}, {0}, {0}, {0}, {0}};
enum {
	NIGHTCLUB, TOWN, DONTCRASH, EVADER, TECHBG
} currentsong;

//----------------------------------------------------------------------------------
// Functions Declaration
//----------------------------------------------------------------------------------
static void UpdateDrawFrame(void);          // Update and draw one frame
static void LoadResources(void);
static void UnloadResources(void);

static void DrawEnvironment(void);

static void InitGame(void);

int main(void)
{
    // Initialization
    //---------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "raylib-5k-jam");

    InitAudioDevice();      // Initialize audio device

	LoadResources();

	InitGame();

	music = bgm[1];
    SetMusicVolume(music, 1.0f);
    PlayMusicStream(music);

    emscripten_set_main_loop(UpdateDrawFrame, 60, 1); // Attach main loop

    // De-Initialization
    //--------------------------------------------------------------------------------------

    // Unload resources
	UnloadResources();

    CloseAudioDevice();     // Close audio context

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

// Update and draw game frame
static void UpdateDrawFrame(void)
{
	if (mute)
	{
		SetMusicVolume(music, 0.0f);
	}
	else
	{
		SetMusicVolume(music, 1.0f);
	}

    // Update
    //----------------------------------------------------------------------------------
    UpdateMusicStream(music);
	frametime = GetFrameTime();
	UpdatePlayer();

	Vector2 dest = GetMousePosition();
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		SetPlayerDestination(dest);
	else if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
	{
		if (!CheckCollisionPointCircle(dest, __player.next, PLAYER_RADIUS))
		{
			SetPlayerDestination(dest);
		}
	}

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(colors[4]);

		DrawEnvironment();

		DrawPlayer();

		DrawText(TextFormat("x %.1f y %.1f _x %.1f _y %.1f", __player.last.x, __player.last.y, __player.next.x, __player.last.y), 10, 10, 20, BLACK);

		if(Button((Rectangle){screenWidth - 190, screenHeight - 90, 180, 80}, colors[2], "MUTE"))
			mute = !mute;

    EndDrawing();
    //----------------------------------------------------------------------------------
}

static void LoadResources(void)
{
    // Load global data (assets that must be available in all screens, i.e. font)
    music = LoadMusicStream("resources/ambient.ogg");

	bgm[0] = LoadMusicStream("resources/nightclub.ogg");
	bgm[1] = LoadMusicStream("resources/town.ogg");
	bgm[2] = LoadMusicStream("resources/dontcrash.ogg");
	bgm[3] = LoadMusicStream("resources/evader.ogg");
	bgm[4] = LoadMusicStream("resources/techbg.ogg");

	// other intialization
	SetColorPalette(0);
}

static void UnloadResources(void)
{
    UnloadMusicStream(music);

	for(int i = 0; i < 5; i++)
		UnloadMusicStream(bgm[i]);
}

static void DrawEnvironment(void)
{
	DrawRectangle(0,0,screenWidth, 100, colors[0]);
	DrawRectangle(0,screenHeight-100,screenWidth, 100, colors[0]);
}

static void InitGame(void)
{
	InitPlayer((Vector2){screenWidth/2, screenHeight/2});


}