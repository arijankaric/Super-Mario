#pragma once

#include "Mario.hpp"
#include "PiranhaTimerDown.hpp"
#include "PiranhaTimerUp.hpp"
#include <vector>
#include <algorithm>

//extern Object foreground;
//extern Mario mario;
//extern Object goomba;
//extern Object ground;
//extern Object initial_ground;

//extern Object mario;
//extern Object *initial_ground_first;
//extern Object *initial_ground_second;
//extern Object *initial_ground_third;
//extern Object *death_ground;

extern const int ID_TIMER;
extern const int IDT_TIMER3;
extern const int ID_TIMER_PIRANHA_UP;
extern const int ID_TIMER_PIRANHA_DOWN;

extern const int DX;
extern const int DY;

void CheckInput();
void Update(HWND);
void UpdateObjekat(HWND hwnd, RECT* rect);
void praviUpdate(HWND);
void Render(HWND);
void Initalize(HWND);
bool UpdatePositionOfObjects(int dx, int dy);
