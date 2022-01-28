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
#include <time.h>
#include <stdlib.h>

#include "constants.h"
#include "player.h"
#include "colors.h"
#include "buttons.h"
#include "menu.h"
#include "state.h"

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
// Constants
NPatchInfo buttonNfo;
const Rectangle muteButton = {screenWidth - 190, screenHeight - 90, 180, 80};

// Variable
Music music = { 0 };
float frametime = 0.0f;
player __player = {0};
/** | colors[0] environment | colors[1] player | colors[2] NONE | colors[3] NONE | colors[4] background | */
Color colors[5] = { {0}, {0}, {0}, {0}, {0} };
bool mute = false;
int level;

//----------------------------------------------------------------------------------
// Resources
//----------------------------------------------------------------------------------
Music bgm[6] = { {0}, {0}, {0}, {0}, {0}, {0}};
typedef enum SongName {
	NIGHTCLUB, TOWN, DONTCRASH, EVADER, TECHBG, HENCHMEN
} SongName;
Texture2D atlas;

//----------------------------------------------------------------------------------
// Functions Declaration
//----------------------------------------------------------------------------------
static void UpdateDrawFrame(void);          // Update and draw one frame
static void LoadResources(void);
static void UnloadResources(void);

void DrawEnvironment(void);
void UpdateEnvironment(void);
void ChangeMusic(int trackno);

static void InitGame(void);

int main(void)
{
    // Initialization
    //---------------------------------------------------------
    srand(time(0));
	InitWindow(screenWidth, screenHeight, "raylib-5k-jam");

    InitAudioDevice();      // Initialize audio device

	LoadResources();

	InitGame();

    SetMusicVolume(music, 1.0f);
	// music = bgm[1];
    // PlayMusicStream(music);
	ChangeMusic(1);

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
    // Update
    //----------------------------------------------------------------------------------
	Vector2 volumes = GetVolume();
    UpdateMusicStream(music);
	frametime = GetFrameTime();
	
	if (mute)
	{
		SetMusicVolume(music, 0.0f);
	}
	else
	{
		SetMusicVolume(music, volumes.x);
	}

	// update buttons
	ButtonToggle(muteButton, colors[2], "MUTE", false, &mute);

	GameState gamestate = GetGameState();
	switch(gamestate)
	{
		case GAMESTATE_menu: MenuMainMenu(false); break;
		case GAMESTATE_play: Game(false); break;
		case GAMESTATE_lose: MenuLoseScreen(false); break;
		case GAMESTATE_win: MenuWinScreen(false); break;
		case GAMESTATE_settings: MenuSettings(false); break;
	}

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

		switch(gamestate)
		{
			case GAMESTATE_menu: 	MenuMainMenu(true); break;
			case GAMESTATE_play: 	Game(true); 		break;
			case GAMESTATE_lose: 	MenuLoseScreen(true); break;
			case GAMESTATE_win: 	MenuWinScreen(true); break;
			case GAMESTATE_settings: MenuSettings(true); break;
		}
        // ClearBackground(colors[4]);

		// DrawEnvironment();
		// DrawPlayer();
		// DrawText(TextFormat("player_acc %.1f", __player.acceleration), 10, 10, 20, BLACK);

		ButtonToggle(muteButton, colors[2], "MUTE", true, &mute);

    EndDrawing();
    //----------------------------------------------------------------------------------
}

static void LoadResources(void)
{
    // Load global data (assets that must be available in all screens, i.e. font)
    // music = LoadMusicStream("resources/ambient.ogg");

	bgm[0] = LoadMusicStream("resources/nightclub.ogg");
	bgm[1] = LoadMusicStream("resources/town.ogg");
	bgm[2] = LoadMusicStream("resources/dontcrash.ogg");
	bgm[3] = LoadMusicStream("resources/evader.ogg");
	bgm[4] = LoadMusicStream("resources/techbg.ogg");
	bgm[5] = LoadMusicStream("resources/henchmen.ogg");

	// other intialization
	SetColorPalette(0);
	buttonNfo = (NPatchInfo){
		(Rectangle){0,0,49,49},
		24, 24, 24, 24,
		NPATCH_NINE_PATCH
	};
	atlas = LoadTexture("resources/atlas.png");
}

static void UnloadResources(void)
{
    UnloadMusicStream(music);

	for(int i = 0; i < 5; i++)
		UnloadMusicStream(bgm[i]);
}

void DrawEnvironment(void)
{
	DrawRectangle(0,0,screenWidth, 100, colors[0]);
	DrawRectangle(0,screenHeight-100,screenWidth, 100, colors[0]);
}

void UpdateEnvironment(void)
{
	// TODO make the game
}

void ChangeMusic(int trackno)
{
	StopMusicStream(music);
	music = bgm[trackno];
	PlayMusicStream(music);
}

static void InitGame(void)
{
	InitPlayer((Vector2){screenWidth/2, screenHeight/2});

	ChangeGameState(GAMESTATE_menu);
	level = 0; // not in a level
}