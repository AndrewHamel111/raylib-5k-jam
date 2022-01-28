#include "buttons.h"

extern Texture2D atlas;
extern NPatchInfo buttonNfo;

bool Button(Rectangle rectangle, Color color, const char* label, bool draw)
{
	// modify color
	bool hover = CheckCollisionPointRec(GetMousePosition(), rectangle);

	NPatchInfo tempNfo = buttonNfo;

	if (draw)
	{
		int textLeft = 15;
		float fst = rectangle.height-20;
		float fontSize = (fst)/(MeasureText(label, fst)/(rectangle.width-(textLeft*2)));
		float textposY = rectangle.y + (((rectangle.height+10) - fontSize)/2);
		// add padding for the bottom of the npatch
		textposY -= tempNfo.bottom;

		if (hover)
		{
			if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
			{
				color.r *= (color.r > 255/2) ? 0.5f : 1.5f;
				color.g *= (color.g > 255/2) ? 0.5f : 1.5f;
				color.b *= (color.b > 255/2) ? 0.5f : 1.5f;

				tempNfo.source.y -= 6;
				textposY += 6;
			}
			else
			{
				color.r *= (color.r > 255/2) ? 0.75f : 1.25f;
				color.g *= (color.g > 255/2) ? 0.75f : 1.25f;
				color.b *= (color.b > 255/2) ? 0.75f : 1.25f;
			}
		}
		
		Vector2 origin = {0,0};
		SetTextureWrap(atlas, TEXTURE_WRAP_CLAMP);
		DrawTextureNPatch(atlas, tempNfo, rectangle, origin, 0.0f, color);

		DrawText(label, rectangle.x + textLeft, textposY, fontSize, (Color){0x14,0x14,0x14,0xff});
	}

	return hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

void ButtonToggle(Rectangle rectangle, Color color, const char* label, bool draw, bool* toggle)
{
	if (draw)
	{
		NPatchInfo tempNfo = buttonNfo;
		int textLeft = 15;
		float fst = rectangle.height-30;
		float fontSize = (fst)/(MeasureText(label, fst)/(rectangle.width-(textLeft*2)));
		float textposY = rectangle.y + (((rectangle.height+15) - fontSize)/2);
		// add padding for the bottom of the npatch
		textposY -= tempNfo.bottom/4;

		if (*toggle)
		{
			tempNfo.source.y -= 6;
			textposY += 6;
		}
		
		Vector2 origin = {0,0};
		SetTextureWrap(atlas, TEXTURE_WRAP_CLAMP);
		DrawTextureNPatch(atlas, tempNfo, rectangle, origin, 0.0f, color);

		DrawText(label, rectangle.x + textLeft, textposY, fontSize, (Color){0x14,0x14,0x14,0xff});
	}
	else
	{
		if (CheckCollisionPointRec(GetMousePosition(), rectangle) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			*toggle = !(*toggle);
	}
}

void Slider(Rectangle rectangle, Color color_bg, Color color_fg, Color color_fill, float* value, bool draw)
{
	if (draw)
	{
		// draw
		DrawRectangleRec(rectangle, color_bg);

		Rectangle _rectangle = rectangle;
		_rectangle.width = *value * rectangle.width;
		DrawRectangleRec(_rectangle, color_fill);

		DrawRectangleLinesEx(rectangle, 0.1f * rectangle.height, color_fg);
	}
	else
	{
		// update
		Vector2 mousepos = GetMousePosition();
		if (CheckCollisionPointRec(mousepos, rectangle) && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			*value = ((mousepos.x - rectangle.x)/rectangle.width);
	}
}