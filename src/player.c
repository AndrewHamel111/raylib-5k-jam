#include "player.h"

#include "easings.h"
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
	{
		__player.last = __player.position;
		__player.next = dest;

		float length = Vector2Length(Vector2Subtract(__player.next, __player.last));
		if (length < 10) return;

		__player.next_time = (Vector2){GetTime(), length/PLAYER_SPEED};
		__player.moving = true;
	}
}

void InitPlayer(Vector2 pos)
{
	__player.position = pos;
	__player.last = __player.next = __player.position;
	__player.next_time = (Vector2){0,0};
	__player.moving = false;
}

void UpdatePlayer(void)
{
	if (__player.moving)
	{
		__player.position.x = EaseCubicInOut(GetTime() - __player.next_time.x, __player.last.x, __player.next.x - __player.last.x, __player.next_time.y);
		__player.position.y = EaseCubicInOut(GetTime() - __player.next_time.x, __player.last.y, __player.next.y - __player.last.y, __player.next_time.y);

		if (GetTime() >= (__player.next_time.x + __player.next_time.y))
		{
			__player.moving = false;
			__player.position = __player.next;
		}
	}

}

void DrawPlayer(void)
{
	DrawCircleV(__player.position, PLAYER_RADIUS, colors[1]);
}