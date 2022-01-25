#ifndef PLAYER_H_
#define PLAYER_H_

#include "raylib.h"

/**
 * \brief Rate of acceleration for player
 */
#define PLAYER_ACC 150
/**
 * \brief Maximum distance from which player will snap to it's destination
 */
#define PLAYER_SNAP_DISTANCE 20
/**
 * \brief Player must be moving slower than this to snap to it's destination.
 */
#define PLAYER_SNAP_SPEED 40
/**
 * \brief Radius of player circle, for both collision and drawing
 */
#define PLAYER_RADIUS 30

typedef struct player
{
	Vector2 position;
	Vector2 velocity;

	Vector2 destination;
} player;

void SetPlayerDestination(Vector2 dest);

void UpdatePlayer();
void DrawPlayer();

#endif