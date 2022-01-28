#ifndef PLAYER_H_
#define PLAYER_H_

#include "raylib.h"

/** \brief Speed of player */
#define PLAYER_SPEED 1000
/** \brief Speed of player */
#define PLAYER_ACC 250
/** \brief Radius of player circle, for both collision and drawing */
#define PLAYER_RADIUS 30

typedef struct player
{
	/** Player's current pos */
	Vector2 position;
	/** Player's current destination (ending point of easing) */
	Vector2 next;
	/** Player's current acceleration. Normalized float that slowly increases as the player continuously holds mousebutton.*/
	float acceleration;
} player;

void SetPlayerDestination(Vector2 dest);

void InitPlayer(Vector2);
void UpdatePlayer(void);
void DrawPlayer(void);

#endif