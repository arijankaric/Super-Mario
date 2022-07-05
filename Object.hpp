#pragma once

#include <windows.h>
#include <iostream>
#include "Global.hpp"

class Object
{
protected:
    BITMAP bitmap;

public:
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
    int Y = 0;

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

    int testingY;
    int testingX;

    bool outline = false;
    virtual bool checkX(std::shared_ptr<Object> obj);
    virtual bool checkY(std::shared_ptr<Object> obj);
    virtual bool checkBottom(std::shared_ptr<Object> obj) = 0;
    virtual bool checkTop(std::shared_ptr<Object> obj) = 0;
    virtual bool checkLeft(std::shared_ptr<Object> obj) = 0;
    virtual bool checkRight(std::shared_ptr<Object> obj) = 0;
    virtual void draw(HDC hdcBuffer, HDC hdcMem);
    ~Object();
    virtual void moveY(std::shared_ptr<Object> obj, bool whosMoving);
    virtual void moveX(std::shared_ptr<Object> obj, bool whosMoving);
    std::string&& getStringTypeOfObject(std::shared_ptr<Object> obj);

    std::shared_ptr<Object> sharedPtr; // pointing to self
};

extern HWND hwnd;
extern std::vector <std::shared_ptr<Object>> objects;
