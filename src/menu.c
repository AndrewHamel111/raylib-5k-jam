#include "menu.h"

#include "raylib.h"
#include "constants.h"

#include "buttons.h"
#include "state.h"

// externs
extern Color colors[5];
extern void DrawEnvironment(void);
extern void DrawPlayer(void);
extern void UpdateEnvironment(void);
extern void UpdatePlayer(void);

// statics
static float musicvol = 1.0f;
static float sfxvol = 1.0f;

void MenuMainMenu(bool draw)
{
	if (draw)
	{
		DrawText("MAIN MENU", 100, 100, 50, colors[1]);
		Button((Rectangle){300,200,300,187}, colors[1], "PLAY", true);
		Button((Rectangle){300,400,300,187}, colors[1], "SETTINGS", true);
	}
	else
	{
		if(Button((Rectangle){300,200,300,187}, colors[1], "PLAY", false))
			ChangeGameState(GAMESTATE_play);
		if(Button((Rectangle){300,400,300,187}, colors[1], "SETTINGS", false))
			ChangeGameState(GAMESTATE_settings);
	}
}

void MenuLoseScreen(bool draw)
{
	if (draw)
	{
		ClearBackground(colors[3]);
		
		DrawText("YOU LOSE!",200,200,50,colors[2]);
		Button((Rectangle){100, screenHeight-190,200,180}, colors[0], "MENU", true);
		Button((Rectangle){400, screenHeight-190,400,180}, colors[0], "AGAIN..", true);
	}
	else
	{
		if(Button((Rectangle){100, screenHeight-190,200,180}, colors[0], "MENU", false))
			ChangeGameState(GAMESTATE_menu);
		if(Button((Rectangle){400, screenHeight-190,400,180}, colors[0], "AGAIN!", false))
			ChangeGameState(GAMESTATE_play);
	}
}

void MenuWinScreen(bool draw)
{
	if (draw)
	{
		ClearBackground(colors[4]);
		
		DrawText("YOU WIN!",200,200,50,colors[1]);
		Button((Rectangle){100, screenHeight-190,200,180}, colors[0], "MENU", true);
		Button((Rectangle){400, screenHeight-190,400,180}, colors[0], "AGAIN!", true);
	}
	else
	{
		if(Button((Rectangle){100, screenHeight-190,200,180}, colors[0], "MENU", false))
			ChangeGameState(GAMESTATE_menu);
		if(Button((Rectangle){400, screenHeight-190,400,180}, colors[0], "AGAIN!", false))
			ChangeGameState(GAMESTATE_play);
	}
}

void MenuSettings(bool draw)
{
	if (draw)
	{
		ClearBackground(colors[4]);

		DrawText("SETTINGS", 200, 30, 50, colors[1]);

		DrawText("MUSIC VOLUME",100,100, 30, colors[0]);
		Slider((Rectangle){100,140,400,100}, colors[4], colors[0], colors[1], &musicvol, true);

		DrawText("SFX VOLUME",100,300, 30, colors[0]);
		Slider((Rectangle){100,340,400,100}, colors[4], colors[0], colors[1], &sfxvol, true);

		Button((Rectangle){100,500,200,90}, colors[0], "RESET PROGRESS", true);

		Button((Rectangle){400,500,200,90}, colors[0], "BACK", true);
	}
	else
	{
		Slider((Rectangle){100,140,400,100}, colors[4], colors[0], colors[1], &musicvol, false);
		Slider((Rectangle){100,340,400,100}, colors[4], colors[0], colors[1], &sfxvol, false);
		if(Button((Rectangle){100,500,200,90}, colors[0], "RESET PROGRESS", false))
		{
			// TODO handle progress reset
		}
		else if(Button((Rectangle){400,500,200,90}, colors[0], "BACK", true))
		{
			ChangeGameState(GAMESTATE_menu);
		}
	}
}

void Game(bool draw)
{
	if (draw)
	{
		DrawPlayer();
		DrawEnvironment();
	}
	else
	{
		UpdatePlayer();
		UpdateEnvironment();
	}
}

Vector2 GetVolume(void)
{
	return (Vector2){musicvol, sfxvol};
}