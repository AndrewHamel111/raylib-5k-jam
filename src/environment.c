#include "environment.h"

#include "raylib.h"
#include "raymath.h"
#include "constants.h"
#include "player.h"

#include <stdlib.h>
#include <time.h>

#define OBSTACLE_SPACING 1.0f
#define OBSTACLE_SPACING_ABS 800.0f

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

	if (!IsPlayerVulnerable()) return;

	Vector2 playerpos = GetPlayerPos();
	bool check = false;
	if (obstacle->shape == OB_rectangle)
	{
		Rectangle rec = (Rectangle){
			obstacle->pos.x - obstacle->rectangle.size.x/2,
			obstacle->pos.y - obstacle->rectangle.size.y/2,
			obstacle->rectangle.size.x,
			obstacle->rectangle.size.y
		};
		if (CheckCollisionCircleRec(playerpos, PLAYER_RADIUS, rec))
			check = true;
	}
	else if (obstacle->shape == OB_triangle)
	{
		//TODO replace this with proper triangle collision
		if (CheckCollisionCircles(playerpos, PLAYER_RADIUS, obstacle->pos, obstacle->triangle.radius*0.66f))
			check = true;
	}
	else if (obstacle->shape == OB_circle)
	{
		if (CheckCollisionCircles(playerpos, PLAYER_RADIUS, obstacle->pos, obstacle->circle.radius))
			check = true;
	}
	
	if (check)
	{
		HurtPlayer();
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
		Vector2 origin = {rec.width/2, rec.height/2};
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

	DrawCircleV(obstacle.pos, 5, RED);
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

	set.obstacles[0].pos.x = screenWidth;

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
	set->obstacles[0].pos.x = screenWidth;
	if (set->lastindex >= (set->length - 15))
	{
		// set has very limited room and the appropriate obstacle must be chosen
	}
	else
	{
		int* i = &(set->lastindex);
		Obstacle prev = set->obstacles[(*i)++];

		// if (*i - 1 <= 0)
		// {
		// 	set->obstacles[*i].pos.x = screenWidth + OBSTACLE_SPACING;
		// }
		Obstacle o = EmptyObstacle();

		if (rand() % 12)
			o.pos.x = prev.pos.x + (speed + OBSTACLE_SPACING);
		else
			o.pos.x = prev.pos.x + (speed + (2*OBSTACLE_SPACING));

		int r = rand() % 6;
		/*	DESIGNING OBSTACLES

		use set->obstacles[(*i)++] = to add extra pieces early. the last set->obstacles[(*i)] call doesn't increment because we want the value at i to be the last valid index.

		*/
		switch(r)
		{
			case 0:
				if (rand() % 5)
				{
					o.pos.y = screenHeight/2;
					o.shape = OB_rectangle;
					o.rectangle.size = (Vector2){50,200};
					o.type = OB_static;
				}
				else
				{
					// adds 2 objects instead of 1
					o.pos.y = 200+75/2;
					o.shape = OB_rectangle;
					o.rectangle.size = (Vector2){50,75};
					o.type = OB_static;

					set->obstacles[(*i)++] = o;

					o.pos.y = screenHeight-200-75/2;
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
				o.circle.radius = GetRandomValue(15,50);
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
						GetRandomValue(o.pos.x, o.pos.x + (speed + OBSTACLE_SPACING)),
						GetRandomValue(150, screenHeight - 150)
					};
				}
				break;
			case 3: // mini hallway
				o.pos.y = 150;
				o.shape = OB_rectangle;
				o.rectangle.size = (Vector2){50, 100};
				o.type = OB_static;
				set->obstacles[(*i)++] = o;

				o.pos.x += (OBSTACLE_SPACING + speed)/2;
				o.pos.y = screenHeight - 150;
				set->obstacles[(*i)++] = o;

				o.pos.x += (OBSTACLE_SPACING + speed)/2;
				o.pos.y = GetRandomValue(screenHeight/2 - 50, screenHeight/2 + 50);
				o.rectangle.size.y *= 2;
				set->obstacles[(*i)++] = o;

				o.pos.x += (OBSTACLE_SPACING + speed)/2;
				o.pos.y = 150;
				o.rectangle.size = (Vector2){50, 100};
				set->obstacles[(*i)++] = o;

				o.pos.y = screenHeight - 150;
				break;
			case 4: // big chungus triangle
				o.pos.y = screenWidth/2;
				o.shape = OB_triangle;
				o.triangle.radius = screenHeight*0.4f;
				o.type = OB_rotating;
				o.rotating.rotation = 0;
				o.rotating.rotation_speed = 180.0f;
				if (!(rand() % 5))
					o.rotating.rotation_speed = GetRandomValue(90.0f, 360.0f);
				break;
			case 5: // triangle starfield

				o.shape = OB_triangle;
				o.type = OB_rotating;
				o.rotating.rotation_speed = GetRandomValue(45.0f, 90.0f + 45.0f);
				int starcount = 5 * (rand() % 3);
				for(int j = 0; j < starcount; j++)
				{
					if (j != 0) // for all but first star
					{
						set->obstacles[(*i)++] = o;
						o.pos.x += (OBSTACLE_SPACING + speed)/3;
					}

					o.pos.y = GetRandomValue(150, screenHeight - 150);
					o.rotating.rotation = GetRandomValue(0, 359.0f);
					o.triangle.radius = GetRandomValue(10, 40);
				}
				break;
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

		set->obstacles[*i] = o;
	}
}