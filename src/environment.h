#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include "raylib.h"

typedef struct Obstacle
{
	Vector2 pos;
	enum {
		OB_rectangle,
		OB_triangle,
		OB_circle
	} shape;
	union 
	{
		struct
		{
			Vector2 size;
		} rectangle;
		struct
		{
			float radius;
		} triangle;
		struct
		{
			float radius;
		} circle;
	};
	enum {
		OB_static,
		OB_rotating,
		OB_moving
	} type;
	union
	{
		struct
		{
			float rotation;
			float rotation_speed;
		} rotating;
		struct
		{
			Vector2 start;
			Vector2 end;
			float t;
			float delta; // direction of the lerp
		} moving;
	};
} Obstacle;

void UpdateObstacle(Obstacle* obstacle, float speed);
void DrawObstacle(Obstacle obstacle);

typedef struct ObstacleSet
{
	Obstacle* obstacles;
	int length;
	int lastindex;
	int difficulty;
} ObstacleSet;

ObstacleSet CreateObstacleSet(Obstacle obstacles[], int obstaclecount, int setlength, int difficulty);
void UpdateObstacleSet(ObstacleSet* set, float speed);
void DrawObstacleSet(ObstacleSet set);

void AddObstacle(ObstacleSet* set, float speed);

#endif