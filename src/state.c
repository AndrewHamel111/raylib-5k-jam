#include "state.h"

extern void ChangeMusic(int trackno);
extern int level;
GameState _gamestate;

GameState ChangeGameState(GameState state)
{
	GameState old = _gamestate;
	_gamestate = state;

	switch(state) // change track as needed
	{
		case GAMESTATE_menu: 
			if (old != GAMESTATE_settings)
				ChangeMusic(1);
			break;
		case GAMESTATE_play: 
			// TEMPORARY, ALWAYS LEVEL 1
			level = 1;
			if (level == 1)
				ChangeMusic(0);
			else if (level == 2)
				ChangeMusic(2);
			else if (level == 3)
				ChangeMusic(3);
			break;
		case GAMESTATE_lose: ChangeMusic(4); break;
		case GAMESTATE_win: ChangeMusic(5); break;
		case GAMESTATE_settings: break;
	}

	return old;
}

GameState GetGameState(void)
{
	return _gamestate;
}