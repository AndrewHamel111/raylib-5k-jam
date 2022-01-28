#include "player.h"

#include "easings.h"
#include "raymath.h"
#include <stdio.h> // DEBUG

extern float frametime;
extern player __player;
extern Color colors[5];

// static Vector2 Vector2ReduceValue(Vector2 v, float value)
// {
// 	if (v.x > value)
// 		v.x -= value;
// 	else if (v.x < -value)
// 		v.x += value;
// 	else
// 		v.x = 0;

// 	if (v.y > value)
// 		v.y -= value;
// 	else if (v.y < -value)
// 		v.y += value;
// 	else
// 		v.y = 0;

// 	return v;
// }

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
		__player.next = dest;
}

void InitPlayer(Vector2 pos)
{
	__player.next = __player.position = pos;
}

void UpdatePlayer(void)
{
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
	
	// input
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		__player.acceleration += 2 * frametime;
	else
		__player.acceleration -= 4 * frametime;

	// clamp player acceleration to [0.0, 1.0]
	if (__player.acceleration > 1.0f)
		__player.acceleration = 1.0f;
	else if (__player.acceleration < 0.0f)
		__player.acceleration = 0.0f;

	// move player
	if (__player.acceleration > 0.0f)
		__player.position = Vector2Add(__player.position, Vector2Scale(Vector2Normalize(Vector2Subtract(__player.next, __player.position)), __player.acceleration * PLAYER_SPEED * frametime));

	// player snapping
	if (CheckCollisionPointCircle(__player.next, __player.position, PLAYER_RADIUS/3))
	{
		// __player.position = __player.next;
		__player.next = __player.position;
		// __player.acceleration = 0;
	}
}

void DrawPlayer(void)
{
	DrawCircleV(__player.position, PLAYER_RADIUS, colors[1]);
}