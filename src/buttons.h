#ifndef BUTTONS_H_
#define BUTTONS_H_

#include "raylib.h"

bool Button(Rectangle rectangle, Color color, const char* label, bool draw);
void ButtonToggle(Rectangle rectangle, Color color, const char* label, bool draw, bool* toggle);
void Slider(Rectangle rectangle, Color color_bg, Color color_fg, Color color_fill, float* value, bool draw);

#endif