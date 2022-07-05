#include "Mario.hpp"

Mario::Mario(int x, int y)
{
    this->hbm_ = hbmMarioWalkRight;
    this->hbmMask_ = hbmMarioWalkRightMask;
    GetObject(hbm_, sizeof(BITMAP), &bitmap);
    this->typeOfObject = MARIO;
    this->width = bitmap.bmWidth/3;
    this->height = bitmap.bmHeight/10;
    this->y = VISINAPROZORA - 80;
    this->x = SIRINAPROZORA/2-this->width/2;
    this->dx = 5;
    this->bottomSide = 25;
    this->leftSide = 12;
    this->rightSide = 24;
    this->topSide = 10;
    this->outline = true;
}

bool Mario::checkLeft(std::shared_ptr<Object> obj)
{
    return true;
}

bool Mario::checkRight(std::shared_ptr<Object> obj)
{
    return true;
}

bool Mario::checkTop(std::shared_ptr<Object> obj)
{
    return true;
}

bool Mario::checkBottom(std::shared_ptr<Object> obj)
{
    return true;
}

void Mario::setWalkLeft()
{
    this->hbm_ = this->hbmMarioWalkLeft;
    this->hbmMask_ = this->hbmMarioWalkLeftMask;
}

void Mario::setWalkRight()
{
    this->hbm_ = this->hbmMarioWalkRight;
    this->hbmMask_ = this->hbmMarioWalkRightMask;
}
