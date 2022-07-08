#include "distanceBetweenObjects.hpp"

bool Object::checkX(std::shared_ptr<Object> obj, int dx) // checkXFuture, napravi checkXCurrent(bez int dx)
{
    return ((checkLeft(obj, dx)) || (checkRight(obj, dx)));
}

bool Object::checkY(std::shared_ptr<Object> obj, int dy) // checkYFuture, napravi checkYCurrent(bez int dy)
{
    return ((checkTop(obj, dy)) || (checkBottom(obj, dy)));
}

Object::~Object()
{
    std::cout << "Object destructor: " << getStringTypeOfObject(this) << std::endl;
}

void Object::moveX(std::shared_ptr<Object> obj, bool whosMoving)
{
    if(whosMoving) // this is moving
    {
//        std::cout << getStringTypeOfObject(this) << " is moving on X " << whosMoving << std::endl;
        int endPointX = this->x + this->dx;
        for(const auto& objTest : *objects)
        {
//            if(distanceBetweenObjects(this, objTest.get()) > 100)
//                continue;

            this->testingX = this->x;
            int directionX;
            if(this->dx == 0)
            {
                return;
                directionX = 0;
            }
            else
                directionX = this->dx/abs(this->dx);
            while(this->testingX != endPointX)
            {
                if(objTest->checkRight(obj, directionX))
                {
                    break;
                }
                else if(objTest->checkLeft(obj, directionX))
                {
                    break;
                }
                this->testingX += directionX;
            }
            if(((this->testingX < endPointX) && directionX > 0) || ((this->testingX > endPointX) && directionX < 0))
                endPointX = this->testingX;
        }
        this->dx = (endPointX - this->x);
//        this->x += this->dx;
    }
    else // obj is moving
    {
        obj->testingX = obj->x;
        int directionX;
        if(obj->dx == 0)
            directionX = 0;
        else
            directionX = obj->dx/abs(obj->dx);
        int endPoint = obj->x + obj->dx;
        while(obj->testingX != endPoint)
        {
            if(checkLeft(obj, directionX))
                break;
            else if(checkRight(obj, directionX))
                break;
            obj->testingX += directionX;
        }
        obj->x += obj->dx;
    }
}

void Object::moveY(std::shared_ptr<Object> obj, bool whosMoving) // limits dy, so it doesn't go too far
{
    if(whosMoving) // this is moving
    {
//        std::cout << getStringTypeOfObject(this) << " is moving on Y " << whosMoving << std::endl;
        int endPointY = this->y + this->dy;
        for(const auto& objTest : *objects)
        {
//            if(distanceBetweenObjects(this, objTest.get()) > 100)
//                continue;

            this->testingY = this->y;
            int directionY;
            if(this->dy == 0)
            {
                return;
                directionY = 0;
            }
            else
                directionY = this->dy/abs(this->dy);
            while(this->testingY != endPointY)
            {
                if(objTest->checkBottom(obj, directionY))
                {
                    break;
                }
                else if(objTest->checkTop(obj, directionY))
                {
                    break;
                }
                this->testingY += directionY;
            }
            if(((this->testingY < endPointY) && directionY > 0) || ((this->testingY > endPointY) && directionY < 0))
                endPointY = this->testingY;
        }
        this->dy = (endPointY - this->y);
//        this->y += this->dy;

    }
    else // obj is moving
    {
        std::cout << getStringTypeOfObject(obj) << " is moving on Y " << whosMoving << std::endl;
        obj->testingY = obj->y;
        int directionY;
        if(obj->dy == 0)
            directionY = 0;
        else
            directionY = obj->dy/abs(obj->dy);
        int endPoint = obj->y + obj->dy;
        while(obj->testingY != endPoint)
        {
            if(checkBottom(obj, directionY))
                break;
            else if(checkTop(obj, directionY))
                break;
            obj->testingY += directionY;
        }
        obj->y += obj->dy;
    }
}

std::string Object::getStringTypeOfObject(Object* objPtr)
{
    if(objPtr == nullptr)
    {
        return std::string("nullptr");
    }
    switch(objPtr->typeOfObject)
    {
    case PIPE:
        return std::string("PIPE");
    case GOOMBA:
        return std::string("GOOMBA");
    case QUESTIONMARK:
        return std::string("QUESTIONMARK");
    case FLOWER_ENEMY:
        return std::string("FLOWER_ENEMY");
    case COIN:
        return std::string("COIN");
    case MARIO:
        return std::string("MARIO");
    case GROUND:
        return std::string("GROUND");
    default:
        return std::string("unidentified object");
    }
}

std::string Object::getStringTypeOfObject(std::shared_ptr<Object> obj)
{
    if(obj == nullptr)
    {
        return std::string("nullptr");
    }
    switch(obj->typeOfObject)
    {
    case PIPE:
        return std::string("PIPE");
    case GOOMBA:
        return std::string("GOOMBA");
    case QUESTIONMARK:
        return std::string("QUESTIONMARK");
    case FLOWER_ENEMY:
        return std::string("FLOWER_ENEMY");
    case COIN:
        return std::string("COIN");
    case MARIO:
        return std::string("MARIO");
    case GROUND:
        return std::string("GROUND");
    default:
        return std::string("unidentified object");
    }
}

void Object::draw(HDC hdcBuffer, HDC hdcMem)
{
    SelectObject(hdcMem, hbm_);
    BitBlt(hdcBuffer, this->x, this->y, this->width, this->height, hdcMem, this->X * this->width, this->Y * this->height, SRCAND);

    SelectObject(hdcMem, hbmMask_);
    BitBlt(hdcBuffer, this->x, this->y, this->width, this->height, hdcMem, this->X * this->width, this->Y * this->height, SRCPAINT);
}

bool Object::checkXRange(std::shared_ptr<Object> obj) const
{
    if((((this->x + this->leftSide) < (obj->x + obj->rightSide)) && ((this->x + this->rightSide) > (obj->x + obj->leftSide))))
        return true;
    return false;
}

bool Object::checkYRange(std::shared_ptr<Object> obj) const
{
    if(((this->y + this->bottomSide) > (obj->y + obj->topSide)) && ((this->y + this->topSide) < (obj->y + obj->bottomSide)))
        return true;
    return false;
}

bool Object::checkXLeft(std::shared_ptr<Object> obj) const
{
    if((this->x + this->leftSide) == (obj->testingX + obj->rightSide))
        return true;
    return false;
}

bool Object::checkXRight(std::shared_ptr<Object> obj) const
{
    if((this->x + this->rightSide) == (obj->testingX + obj->leftSide))
        return true;
    return false;
}

bool Object::checkYTop(std::shared_ptr<Object> obj) const
{
    if((this->y + this->topSide) == (obj->testingY + obj->bottomSide))
        return true;
    return false;

}

bool Object::checkYBottom(std::shared_ptr<Object> obj) const
{
    if((this->y + this->bottomSide) == (obj->testingY + obj->topSide))
        return true;
    return false;
}

bool Object::checkLeft(std::shared_ptr<Object> obj, int dx)
{
    if(checkXLeft(obj) && checkYRange(obj) && (obj->dx > 0))
    {
        std::cout << "left side " << getStringTypeOfObject(this) << " collided with " << getStringTypeOfObject(obj) << std::endl;
        return true;
    }
    return false;
}

bool Object::checkRight(std::shared_ptr<Object> obj, int dx)
{
    if(checkXRight(obj) && checkYRange(obj) && (obj->dx < 0))
    {
        std::cout << "right side " << getStringTypeOfObject(this) << " collided with " << getStringTypeOfObject(obj) << std::endl;
        return true;
    }
    return false;
}

bool Object::checkTop(std::shared_ptr<Object> obj, int dy)
{
    if(checkYTop(obj) && checkXRange(obj) && (dy > 0))
    {
        std::cout << "topSide of " << getStringTypeOfObject(this) << " collided with bottomSide of " << getStringTypeOfObject(obj) << std::endl;
        return true;
    }
    return false;
}

bool Object::checkBottom(std::shared_ptr<Object> obj, int dy)
{
    if(checkYBottom(obj) && checkXRange(obj) && (dy < 0))
    {
        std::cout << "bottomSide of " << getStringTypeOfObject(this) << " collided with topSide of " << getStringTypeOfObject(obj) << std::endl;
        return true;
    }
    return false;
}

void Object::moveYX(std::shared_ptr<Object> obj, bool whosMoving)
{
    this->moveY(obj, whosMoving);
    this->moveX(obj, whosMoving);
}

void Object::setYState(stateY st)
{
    stY_ = st;
}
void Object::setXState(stateX st)
{
    stX_ = st;
}

void Object::nextDY(void)
{
    // samo za goombe i maria za sada
}

void Object::setDX(int DX)
{

}

void Object::setDY(int DY)
{

}
