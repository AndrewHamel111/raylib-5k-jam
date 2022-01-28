#include "environment.h"

#include "raylib.h"
#include "raymath.h"
#include "constants.h"

#include <stdlib.h>
#include <time.h>

#define OBSTACLE_SPACING 0.5f

extern Color colors[5];
extern float frametime;

////////////////////////////
// OBSTACLE
////////////////////////////
void UpdateObstacle(Obstacle* obstacle, float speed)
{
	obstacle->pos.x -= speed * frametime;

	if (obstacle->type == OB_static) return;

	if (obstacle->type == OB_rotating)
		obstacle->rotating.rotation += obstacle->rotating.rotation_speed * frametime;

	if (obstacle->type == OB_moving)
	{
		obstacle->moving.start.x -= speed * frametime;
		obstacle->moving.end.x -= speed * frametime;

		obstacle->moving.t += obstacle->moving.delta * frametime;
		if (obstacle->moving.t > 1.0f)
		{
			obstacle->moving.t = 1.0f;
			obstacle->moving.delta *= -1.0f;
		}
		else if (obstacle->moving.t < 0.0f)
		{
			obstacle->moving.t = 0.0f;
			obstacle->moving.delta *= -1.0f;
		}
		obstacle->pos = Vector2Lerp(obstacle->moving.start, obstacle->moving.end, obstacle->moving.t);
	}
}

void DrawObstacle(Obstacle obstacle)
{
	if (!CheckCollisionCircleRec(obstacle.pos, 200, (Rectangle){0,0,screenWidth, screenHeight}))
		return;

	float rotation = 0.0f;
	if (obstacle.type == OB_rotating)
		rotation = obstacle.rotating.rotation;

	Color color = colors[0];

	if(obstacle.shape == OB_rectangle)
	{
		Rectangle rec = {obstacle.pos.x, obstacle.pos.y, obstacle.rectangle.size.x, obstacle.rectangle.size.y};
		Vector2 origin = {rec.width, rec.height};
		DrawRectanglePro(rec, origin, rotation, color);
	}
	else if (obstacle.shape == OB_triangle)
	{
		DrawPoly(obstacle.pos, 3, obstacle.triangle.radius, rotation, color);
	}
	else if (obstacle.shape == OB_circle)
	{
		DrawCircleV(obstacle.pos, obstacle.circle.radius, color);
	}
}

static Obstacle EmptyObstacle(void)
{
	Obstacle ob = {0};
	return ob;
}

////////////////////////////
// OBSTACLE SET
////////////////////////////
ObstacleSet CreateObstacleSet(Obstacle obstacles[], int obstaclecount, int setlength, int difficulty)
{
	ObstacleSet set;
	set.length = setlength;
	set.lastindex = obstaclecount - 1;
	set.difficulty = difficulty;
	set.obstacles = (Obstacle*)calloc(setlength, sizeof(Obstacle));
	for(int i = 0; i < set.lastindex; i++)
		set.obstacles[i] = obstacles[i];
	for(int i = set.lastindex + 1; i < setlength; i++)
		set.obstacles[i] = EmptyObstacle();

	return set;
}

void UpdateObstacleSet(ObstacleSet* set, float speed)
{
	for(int i = 0; i < set->length; i++)
		UpdateObstacle(set->obstacles + i, speed);
}

void DrawObstacleSet(ObstacleSet set)
{
	for(int i = 0; i < set.length; i++)
		DrawObstacle(set.obstacles[i]);
}

void AddObstacle(ObstacleSet* set, float speed)
{
	if (set->lastindex >= (set->length - 4))
	{
		// set has no more room, extend it or something
	}
	else
	{
		Obstacle prev = set->obstacles[set->lastindex];
		set->lastindex++;
		int i = set->lastindex;

		Obstacle o = EmptyObstacle();

		if (rand() % 4)
			o.pos.x = prev.pos.x + (speed * OBSTACLE_SPACING);
		else
			o.pos.x = prev.pos.x + (speed * 2.0f * OBSTACLE_SPACING);

		int r = rand() % 3;
		switch(r)
		{
			case 0:
				if (rand() % 5)
				{
					o.pos.y = screenHeight/2;
					o.shape = OB_rectangle;
					o.rectangle.size = (Vector2){50,300};
					o.type = OB_static;
				}
				else
				{
					// adds 2 objects instead of 1
					o.pos.y = 150;
					o.shape = OB_rectangle;
					o.rectangle.size = (Vector2){50,100};
					o.type = OB_static;

					set->obstacles[i] = o;

					o.pos.y = screenHeight - 150;
					if (!(rand() % 3))
					{
						set->obstacles[i] = o;
						
						o.pos.y = screenHeight/2;
						o.rectangle.size.y *= 1.66f;
					}
				}
				break;
			case 1:
				o.pos.y = GetRandomValue(150, screenHeight - 150);
				o.shape = OB_rectangle;
				o.rectangle.size = (Vector2){50*GetRandomValue(1,3),GetRandomValue(50,150)};
				o.type = OB_static;
				break;
			case 2:
				o.pos.y = GetRandomValue(150, screenHeight - 150);
				o.shape = OB_circle;
				o.circle.radius = GetRandomValue(50,100);
				o.type = OB_moving;
				o.moving.t = 0.0f;
				o.moving.delta = 1.0f;
				o.moving.start = (Vector2){o.pos.x, o.pos.y};
				if (rand() % 4)
				{
					o.moving.end = (Vector2){o.pos.x, screenHeight - o.pos.y};
				}
				else
				{
					o.moving.end = (Vector2){
						GetRandomValue(o.pos.x, o.pos.x + (speed * OBSTACLE_SPACING)),
						GetRandomValue(150, screenHeight - 150)
					};
				}
				break;
			// case 3:
			// 	break;
			// case 4:
			// 	break;
			// case 5:
			// 	break;
			// case 6:
			// 	break;
			// case 7:
			// 	break;
			// case 8:
			// 	break;
			// case 9:
			// 	break;
			// case 10:
			// 	break;
			// case 11:
			// 	break;
			// case 12:
			// 	break;
		}

		set->obstacles[i] = o;
	}
}