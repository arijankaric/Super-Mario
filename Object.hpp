#pragma once

#include <windows.h>
#include "Global.hpp"

typedef struct ObjectInfo
{
    int width;
    int height;
    int x;
    int y;

    int dx = 0;
    int dy = 0;

    HBITMAP hbm_;
    HBITMAP hbmMask_;

    int max; // max X cycles through bmp
    int X; // current X cycle through bmp

    int cyclesUntilDeath = -1; // cycles until the object is deleted
    int cyclesForChange = 1; // cycles counter requirement for change of current X to happen
    int changeCycles = 0; // cycles counter until change
    int cycles = 0; // death cycles

    bool flag = false; // is object empty or not, questionBoxObject empty/without coin for example

    int typeOfObject;

    int startingX; // starting positions for objects
    int startingY;

    int objectX = 0; // for marioX
    int objectY = 1; // marioY

    int leftSide;
    int rightSide;
    int topSide;
    int bottomSide;

    int stateY = NEUTRAL;
    int stateX = NEUTRAL;

    void* parent = NULL;

    int ground;

    bool outline = false;
} Object;
