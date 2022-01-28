#ifndef STATE_H_
#define STATE_H_

typedef enum GameState {
	GAMESTATE_menu, GAMESTATE_play, GAMESTATE_lose, GAMESTATE_win, GAMESTATE_settings
} GameState;

/**
 * \brief Set Game State
 * \return Previous State 
 */
GameState ChangeGameState(GameState);
GameState GetGameState(void);

#endif