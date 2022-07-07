#include "distanceBetweenObjects.hpp"

bool Object::checkX(std::shared_ptr<Object> obj, int dx) // checkXFuture, napravi checkXCurrent(bez int dx)
{
    return (checkLeft(obj) && (dx < 0)) || (checkRight(obj) && (dx > 0));
}

bool Object::checkY(std::shared_ptr<Object> obj, int dy) // checkYFuture, napravi checkYCurrent(bez int dy)
{
    return (checkTop(obj) && (dy < 0)) || (checkBottom(obj) && (dy > 0));
}

Object::~Object()
{
    std::cout << "Object destructor: " << getStringTypeOfObject(this) << std::endl;
}

void Object::moveX(std::shared_ptr<Object> obj, bool whosMoving)
{
    if(whosMoving) // this is moving
    {
        for(const auto& objTest : *objects)
        {
            if(distanceBetweenObjects(this, obj.get()) > 100)
                continue;

            this->testingX = this->x;
            int directionX;
            if(this->dx == 0)
                directionX = 0;
            else
                directionX = this->dx/abs(this->dx);
            int endPoint = this->x + this->dx;
            while(this->testingX != endPoint)
            {
                if(checkLeft(objTest))
                    break;
                else if(checkRight(objTest))
                    break;
                this->testingX += directionX;
            }
            this->x += this->dx;
        }
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
            if(checkLeft(obj))
                break;
            else if(checkRight(obj))
                break;
            obj->testingX += directionX;
        }
        obj->x += obj->dx;
    }
}

void Object::moveY(std::shared_ptr<Object> obj, bool whosMoving)
{
    if(whosMoving) // this is moving
    {
        for(const auto& objTest : *objects)
        {
            if(distanceBetweenObjects(this, objTest.get()) > 100)
                continue;

            this->testingY = this->y;
            int directionY;
            if(this->dy == 0)
                directionY = 0;
            else
                directionY = this->dy/abs(this->dy);
            int endPoint = this->y + this->dy;
            while(this->testingY != endPoint)
            {
                if(checkBottom(obj))
                    break;
                else if(checkTop(obj))
                    break;
                this->testingY += directionY;
            }
            this->y += this->dy;
        }
    }
    else // obj is moving
    {
        obj->testingY = obj->y;
        int directionY;
        if(obj->dy == 0)
            directionY = 0;
        else
            directionY = obj->dy/abs(obj->dy);
        int endPoint = obj->y + obj->dy;
        while(obj->testingY != endPoint)
        {
            if(checkBottom(obj))
                break;
            else if(checkTop(obj))
                break;
            obj->testingY += directionY;
        }
        obj->y += obj->dy;
    }
}

std::string&& Object::getStringTypeOfObject(Object* objPtr)
{
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

std::string&& Object::getStringTypeOfObject(std::shared_ptr<Object> obj)
{
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
    if((((this->x + this->leftSide) < (obj->x + obj->rightSide)) && ((this->x + this->leftSide) > (obj->x + obj->leftSide))) || (((this->x + this->rightSide) < (obj->x + obj->rightSide)) && ((this->x + this->rightSide) > (obj->x + obj->leftSide))))
        return true;
    return false;
}

bool Object::checkYRange(std::shared_ptr<Object> obj) const
{
    if((((this->y + this->bottomSide) < (obj->y + obj->bottomSide)) && ((this->y + this->bottomSide) > (obj->y + obj->topSide))) || (((this->y + this->topSide) < (obj->y + obj->bottomSide)) && ((this->y + this->topSide) > (obj->y + obj->topSide))) )
        return true;
    return false;
}

bool Object::checkXLeft(std::shared_ptr<Object> obj) const
{
    if((this->x + this->leftSide) == (obj->x + obj->rightSide))
        return true;
    return false;
}

bool Object::checkXRight(std::shared_ptr<Object> obj) const
{
    if((this->x + this->rightSide) == (obj->x + obj->leftSide))
        return true;
    return false;
}

bool Object::checkYTop(std::shared_ptr<Object> obj) const
{
    if((this->y + this->topSide) == (obj->y + obj->bottomSide))
        return true;
    return false;

}

bool Object::checkYBottom(std::shared_ptr<Object> obj) const
{
    if((this->y + this->bottomSide) == (obj->y + obj->topSide))
        return true;
    return false;
}

bool Object::checkLeft(std::shared_ptr<Object> obj)
{
    if(checkXLeft(obj) && checkYRange(obj))
    {
        std::cout << "left side " << getStringTypeOfObject(this) << " collided with " << getStringTypeOfObject(obj) << std::endl;
        return false;
    }
    return true;
}

bool Object::checkRight(std::shared_ptr<Object> obj)
{
    if(checkXRight(obj) && checkYRange(obj))
    {
        std::cout << "right side " << getStringTypeOfObject(this) << " collided with " << getStringTypeOfObject(obj) << std::endl;
        return false;
    }
    return true;
}

bool Object::checkTop(std::shared_ptr<Object> obj)
{
    if(checkYTop(obj) && checkXRange(obj))
    {
        std::cout << "top side " << getStringTypeOfObject(this) << " collided with " << getStringTypeOfObject(obj) << std::endl;
        return false;
    }
    return true;
}

bool Object::checkBottom(std::shared_ptr<Object> obj)
{
    if(checkYBottom(obj) && checkXRange(obj))
    {
        std::cout << "bottom side " << getStringTypeOfObject(this) << " collided with " << getStringTypeOfObject(obj) << std::endl;
        return false;
    }
    return true;
}
