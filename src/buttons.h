#ifndef BUTTONS_H_
#define BUTTONS_H_

#include "raylib.h"

bool Button(Rectangle rectangle, Color color, const char* label)
{
	// modify color
	bool hover = CheckCollisionPointRec(GetMousePosition(), rectangle);
	if (hover)
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
			color.a *= 0.50f;
		else
			color.a *= 0.75f;

	// display button
	DrawRectangleRec(rectangle, color);
	float fontSize = (rectangle.height-10)/(MeasureText(label, rectangle.height - 10)/(rectangle.width-10));
	DrawText(label, rectangle.x + 5, rectangle.y + (((rectangle.height+10) - fontSize)/2), fontSize, (Color){0x4a,0x3f,0x3c,0xff});

	return hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

#endif