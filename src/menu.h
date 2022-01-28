#ifndef MENU_H_
#define MENU_H_

#include "raylib.h"

void MenuMainMenu(bool);
void MenuLoseScreen(bool);
void MenuWinScreen(bool);
void MenuSettings(bool);
void Game(bool);

Vector2 GetVolume(void);

#endif