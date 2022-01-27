#ifndef PLAYER_H_
#define PLAYER_H_

#include "raylib.h"

/** \brief Speed of player */
#define PLAYER_SPEED 1000
/** \brief Radius of player circle, for both collision and drawing */
#define PLAYER_RADIUS 30

typedef struct player
{
	/** Player's current pos */
	Vector2 position;
	/** Player's last destination (starting point of easing) */
	Vector2 last;
	/** Player's current destination (ending point of easing) */
	Vector2 next;

	/** \brief (Vector2){start_time, end_time} */
	Vector2 next_time;
	
	bool moving;
} player;

void SetPlayerDestination(Vector2 dest);

void InitPlayer(Vector2);
void UpdatePlayer(void);
void DrawPlayer(void);

#endif