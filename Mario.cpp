#include "Mario.hpp"

Mario::Mario(vektorObjekata obj, vektorObjekata movObj, int x, int y)
{
    this->Y = 0;
    this->cyclesForChange = 3;
    this->max = 2;
    this->objects = obj;
    this->movingObjects = movObj;
    this->hbm_ = hbmMarioWalkRight;
    this->hbmMask_ = hbmMarioWalkRightMask;
    GetObject(hbm_, sizeof(BITMAP), &bitmap);
    this->typeOfObject = MARIO;
    this->width = bitmap.bmWidth/3;
    this->height = bitmap.bmHeight/10;
    this->y = 239;
    this->x = SIRINAPROZORA/2-this->width/2;
    this->dx = 5;
    this->dy = 0;
    this->bottomSide = 25;
    this->leftSide = 12;
    this->rightSide = 24;
    this->topSide = 10;
    this->ground = 320;
    this->outline = true;
    this->objectY = 1;
    this->objectX = 0;
}

//bool Mario::checkLeft(std::shared_ptr<Object> obj)
//{
//    if(checkXLeft(obj) && checkYRange(obj))
//    {
//        std::cout << "left side " << getStringTypeOfObject(this) << " collided with " << getStringTypeOfObject(obj) << std::endl;
//        return false;
//    }
//    return true;
//}
//
//bool Mario::checkRight(std::shared_ptr<Object> obj)
//{
//    if(checkXRight(obj) && checkYRange(obj))
//    {
//        std::cout << "right side " << getStringTypeOfObject(this) << " collided with " << getStringTypeOfObject(obj) << std::endl;
//        return false;
//    }
//    return true;
//}
//
//bool Mario::checkTop(std::shared_ptr<Object> obj)
//{
//    if(checkYTop(obj) && checkXRange(obj))
//    {
//        std::cout << "top side " << getStringTypeOfObject(this) << " collided with " << getStringTypeOfObject(obj) << std::endl;
//        return false;
//    }
//    return true;
//}
//
//bool Mario::checkBottom(std::shared_ptr<Object> obj)
//{
//    if(checkYBottom(obj) && checkXRange(obj))
//    {
//        std::cout << "bottom side " << getStringTypeOfObject(this) << " collided with " << getStringTypeOfObject(obj) << std::endl;
//        return false;
//    }
//    return true;
//}

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

void Mario::setYState(stateY st)
{
    if(stateY::Neutral == st)
    {
        if(stX_ == stateX::Neutral)
        {
            Y = 0;
            max = 1;
        }
    }
    else if(st == stateY::Up)
    {
        if(stY_ == stateY::Neutral)
        {
            dy = -22;
        }
        else
        {
            return;
        }
        Y = 3;
        X = 0;
        max = 1;
    }
    else // Down je isto kao i up?
    {

    }
    Object::setYState(st);
}

void Mario::setXState(stateX st)
{
    Object::setXState(st);

    if(stateX::Left == st)
    {
        Y = 1;
        max = 2;
        dx = -5;
        setWalkLeft();
    }
    else if(stateX::Right == st)
    {
        Y = 1;
        max = 2;
        dx = 5;
        setWalkRight();
    }
    else // Neutral
    {
        Y = 0;
        max = 1;
        // setNeutral();?
    }
}

void Mario::nextDY(void)
{
    this->dy += 3;
}
//
//void Mario::nextY(void)
//{
////    this->moveY();?
//}

//void Mario::changeY(int dy)
//{
//    if()
//}
