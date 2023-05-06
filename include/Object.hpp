#pragma once

#include <windows.h>
#include <iostream>
#include "Global.hpp"

//class Mario;

class Object : public std::enable_shared_from_this<Object>
{
protected:
    BITMAP bitmap;

public:
    int life_ = 1;
    int width;
    int height;
    int x;
    int y;

    enum class objectType {Undefined, Mario, Goomba, Ground, Pipe, Turtle, FlowerEnemy, Coin, QuestionBlock, Fireball};
    bool moveable = false; // false because most of objects are moveable
    // Undefined - doesn't matter, for example background

    HBITMAP hbm_;
    HBITMAP hbmMask_;

    int dx_ = 0;
    int dy_ = 0;

    int maxCycles_; // maxCycles_ X cycles through bmp
    int X_; // current X cycle through bmp
    int Y_ = 0;

    int cyclesUntilDeath = -1; // cycles until the object is deleted
    int cycles = 0; // death cycles
    int cyclesForChange = 1; // cycles counter requirement for change of current X to happen
    int changeCycles = 0; // cycles counter until change

    bool flag = false; // is object empty or not, questionBoxObject empty/without coin for example

    objectType typeOfObject = objectType::Undefined;

    int startingX; // starting positions for objects
    int startingY;

//    int objectX = 0; // for marioX
//    int objectY = 1; // marioY

    int leftSide;
    int rightSide;
    int topSide;
    int bottomSide;

    void* parent = NULL;

    int ground;

    int testingY;
    int testingX;

    bool outline = true;
    virtual bool checkX(std::shared_ptr<Object> obj, int dx_); // more like checkXFuture
    virtual bool checkY(std::shared_ptr<Object> obj, int dy_); // checkYFuture
    virtual bool checkBottom(std::shared_ptr<Object> obj, int dy_);
    virtual bool checkTop(std::shared_ptr<Object> obj, int dy_);
    virtual bool checkLeft(std::shared_ptr<Object> obj, int dx_);
    virtual bool checkRight(std::shared_ptr<Object> obj, int dx_);
    virtual void draw(HDC hdcBuffer, HDC hdcMem);
    ~Object();
    virtual void projectY();
    void projectX();
    virtual void moveYX();
    virtual void moveY();
    virtual void moveX();
    static const std::string getStringTypeOfObject(std::shared_ptr<Object> obj);
    static const std::string getStringTypeOfObject(Object* objPtr);
    virtual const std::string getStringTypeOfObject(void) const = 0;
    bool checkXRange(std::shared_ptr<Object> obj) const;
    bool checkYRange(std::shared_ptr<Object> obj) const;
    bool checkYTop(std::shared_ptr<Object> obj) const;
    bool checkYBottom(std::shared_ptr<Object> obj) const;
    bool checkXLeft(std::shared_ptr<Object> obj) const;
    bool checkXRight(std::shared_ptr<Object> obj) const;
    std::shared_ptr<Object> compareObj = nullptr;
    using vektorObjekata = std::shared_ptr<std::vector<std::shared_ptr<Object>>>;
    static vektorObjekata objects;
    static vektorObjekata newObjects;
//    vektorObjekata movingObjects;



    enum class stateY { Up, Down, Neutral};
    enum class stateX { Left, Right, Neutral};
    stateY stY_ = stateY::Neutral;
    stateX stX_ = stateX::Neutral;
    virtual void setYState(stateY st);
    virtual void setXState(stateX st);

//    virtual void nextY(void) = 0;
    virtual void nextdy_(void);


    virtual void setdx_(int dx_);
    virtual void setdy_(int dy_);

    static std::shared_ptr<Object> mario;

    bool collidedx_ = false;
    virtual void collideX(std::shared_ptr<Object> obj);
    virtual void stompY(std::shared_ptr<Object> obj);

//    bool deadly = false;

//    bool checkEdge(std::shared_ptr<Object> obj) const; // checking bottom edges
    bool checkLeftEdge(std::shared_ptr<Object> obj) const; // checking bottom left edge
    bool checkRightEdge(std::shared_ptr<Object> obj) const; // checking bottom right edge

    bool fall = true; // does the object fall when it reaches the edge or not

    unsigned char determineQuadrant() const;
    bool determineSide() const;
    int centerX() const;
    int centerY() const;
    int getBottom() const;
    int getTop() const;
    int getLeft() const;
    int getRight() const;
    void removeDeadObject(std::shared_ptr<Object> obj);
    virtual void afterDraw();
    virtual const bool deadly(const std::shared_ptr<Object> obj) const;
    virtual void decreaseLife();
    virtual void increaseLife();
    DWORD timeOfDeath = 0;
    bool isSprite() const; // tells us if the object should have a sprite assigned(hbm_/hbmMask_)
    bool phases = false; // tells us if the object phases through other object, for instance a fireball phases through all objects except through Mario, since Mario is it's enemy

};
