#include "player.h"

#include "raymath.h"
#include <stdio.h> // DEBUG

extern float frametime;
extern player __player;
extern Color colors[5];

static Vector2 Vector2ReduceValue(Vector2 v, float value)
{
	if (v.x > value)
		v.x -= value;
	else if (v.x < -value)
		v.x += value;
	else
		v.x = 0;

	if (v.y > value)
		v.y -= value;
	else if (v.y < -value)
		v.y += value;
	else
		v.y = 0;

	return v;
}

/**
 * \brief Set the destination of the player to a new position.
 * 
 * \param dest A Vector2 in screenspace.
 */
void SetPlayerDestination(Vector2 dest)
{
	if(!CheckCollisionPointRec(dest, (Rectangle){0,0,GetScreenWidth(),GetScreenHeight()}))
		printf("Tried to set dest outside of screen space.");
	else
		__player.destination = dest;
}

void UpdatePlayer()
{
	// apply acceleration, as needed
	__player.velocity = Vector2Add(__player.velocity, 
		Vector2Scale(Vector2Normalize(Vector2Subtract(__player.destination, __player.position)), PLAYER_ACC * frametime)
	);

	// if the players current position OR next position is close enough to the destination that it should snap to it, do so. This resets the player's velocity as well
	if ( (CheckCollisionPointCircle(__player.position, __player.destination, PLAYER_SNAP_DISTANCE)
		|| CheckCollisionPointCircle(Vector2Add(__player.position, __player.velocity), __player.destination, PLAYER_SNAP_DISTANCE)) && (Vector2Length(__player.velocity) < PLAYER_SNAP_SPEED)
	)
	{
		__player.position = __player.destination;
		__player.velocity = Vector2Zero();
	}

	__player.position = Vector2Add(__player.position, Vector2Scale(__player.velocity, frametime));

	// apply deceleration
	__player.velocity = Vector2ReduceValue(__player.velocity, 0.15f*frametime*PLAYER_ACC);
}

void DrawPlayer()
{
	DrawCircleV(__player.position, PLAYER_RADIUS, colors[1]);
}