#pragma once

#include "Object.hpp"
#include "PiranhaTimerDown.hpp"
#include "PiranhaTimerUp.hpp"
#include <vector>
#include <algorithm>

extern HBITMAP questionMark;
extern HBITMAP questionMarkMask;
extern HBITMAP enemy;
extern HBITMAP enemyMask;
extern HBITMAP coin;
extern HBITMAP coinMask;
extern HBITMAP goomba;
extern HBITMAP goombaMask;
extern HBITMAP ground;
extern HBITMAP groundMask;
extern HBITMAP hbmBackground;
extern HBITMAP hbmMarioWalk;
extern HBITMAP hbmMarioWalkMask;
extern Object *initial_ground_first;
extern Object *initial_ground_second;
extern Object *initial_ground_third;
extern Object *death_ground;
extern std::vector <Object*> objects;

extern Object background;
extern Object foreground;
extern Object mario;
//extern Object goomba;
//extern Object ground;
extern Object initial_ground;

extern Object mario;
extern Object *initial_ground_first;
extern Object *initial_ground_second;
extern Object *initial_ground_third;
extern Object *death_ground;

extern std::vector <Object*> objects;

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
