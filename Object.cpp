//#include "Object.hpp"
#include "distanceBetweenObjects.hpp"

bool Object::checkX(std::shared_ptr<Object> obj)
{
    return checkLeft(obj) && checkRight(obj);
}

bool Object::checkY(std::shared_ptr<Object> obj)
{
    return checkTop(obj) && checkBottom(obj);
}

Object::~Object()
{
    std::cout << "Object destructor" << std::endl;
}

void Object::moveX(std::shared_ptr<Object> obj, bool whosMoving)
{
    if(whosMoving) // this is moving
    {
        for(const auto& objTest : objects)
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
        for(const auto& objTest : objects)
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

bool Object::checkXRange() const
{
    if((((this->x + this->leftSide) < (this->compareObj->x + this->compareObj->rightSide)) && ((this->x + this->leftSide) > (this->compareObj->x + this->compareObj->leftSide))) || (((this->x + this->rightSide) < (this->compareObj->x + this->compareObj->rightSide)) && ((this->x + this->rightSide) > (this->compareObj->x + this->compareObj->leftSide))))
        return true;
    return false;
}

bool Object::checkYRange() const
{
    if((((this->y + this->bottomSide) < (this->compareObj->y + this->compareObj->bottomSide)) && ((this->y + this->bottomSide) > (this->compareObj->y + this->compareObj->topSide))) || (((this->y + this->topSide) < (this->compareObj->y + this->compareObj->bottomSide)) && ((this->y + this->topSide) > (this->compareObj->y + this->compareObj->topSide))) )
        return true;
    return false;
}

bool Object::checkXLeft() const
{
    if((this->x + this->leftSide) == (this->compareObj->x + this->compareObj->rightSide))
        return true;
    return false;
}

bool Object::checkXRight() const
{
    if((this->x + this->rightSide) == (this->compareObj->x + this->compareObj->leftSide))
        return true;
    return false;
}

bool Object::checkYTop() const
{
    if((this->y + this->topSide) == (this->compareObj->y + this->compareObj->bottomSide))
        return true;
    return false;

}

bool Object::checkYBottom() const
{
    if((this->y + this->bottomSide) == (this->compareObj->y + this->compareObj->topSide))
        return true;
    return false;
}
