#ifndef COLORS_H_
#define COLORS_H_

#include "raylib.h"

extern Color colors[5];

Color ColorHex(int hex)
{
	return (Color){
		(hex >> 16) & 0xFF,
		(hex >> 8) & 0xFF,
		hex & 0xFF,
		0xFF
	};
}

// Color ColorHexA(int hex)
// {
// 	return (Color){
// 		(hex >> 32) & 0xFF,
// 		(hex >> 16) & 0xFF,
// 		(hex >> 8) & 0xFF,
// 		hex & 0xFF
// 	};
// }

void SetColorPalette(int palette)
{
	unsigned char i = 0;
	switch(palette)
	{
		case 0:
			colors[i++] = ColorHex(0x498b8e); // cyan
			colors[i++] = ColorHex(0xf28544); // orange
			colors[i++] = ColorHex(0xf9df7f); // yellow
			colors[i++] = ColorHex(0xc0dfad); // very light lime
			colors[i++] = ColorHex(0x4a3f3c); // grape skittle
			break;
		case 1:
			colors[i++] = (Color){0x49,0x8e,0x8b,0xff}; // cyan
			colors[i++] = (Color){0xf2,0x85,0x44,0xff}; // orange
			colors[i++] = (Color){0xf9,0xdf,0x7f,0xff}; // yellow
			colors[i++] = (Color){0xc0,0xdf,0xad,0xff}; // very light lime
			colors[i++] = (Color){0x4a,0x3f,0x3c,0xff}; // grape skittle
			break;
		case 2:
			colors[i++] = (Color){0xf2,0x85,0x44,0xff}; // orange
			colors[i++] = (Color){0xf9,0xdf,0x7f,0xff}; // yellow
			colors[i++] = (Color){0xc0,0xdf,0xad,0xff}; // very light lime
			colors[i++] = (Color){0x49,0x8e,0x8b,0xff}; // cyan
			colors[i++] = (Color){0x4a,0x3f,0x3c,0xff}; // grape skittle
			break;
	}
}

#endif