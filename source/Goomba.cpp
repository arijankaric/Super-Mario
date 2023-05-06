#include "../include/Goomba.hpp"

Goomba::Goomba(int x, int y)
{
    this->typeOfObject = objectType::Goomba;
//    this->objects = obj;
//    this->movingObjects = movObj;
    this->hbm_ = hbmGoomba_;
    this->hbmMask_ = hbmGoombaMask_;

    this->maxCycles_ = 2;
    this->cyclesForChange = 3;
    GetObject(hbm_, sizeof(BITMAP), &bitmap);

    this->width = bitmap.bmWidth/4;
    this->height = bitmap.bmHeight;
    this->y = y;
    this->x = x;
    this->dx_ = -1;
    this->dy_ = 0;
    this->bottomSide = 15;
    this->leftSide = 0;
    this->rightSide = 15;
    this->topSide = 0;
    this->ground = 320;
    this->moveable = true;
}

bool Goomba::checkLeft(std::shared_ptr<Object> obj, int dx_)
{
    if(checkYRange(obj) && checkXLeft(obj) && (obj->dx_ > 0))
    {
        std::cout << "----------------------------------\n";
        std::cout << Object::getStringTypeOfObject(obj) << " hit left side of goomba\n";
        std::cout << "----------------------------------\n";

        if(obj->typeOfObject == objectType::Mario)
        {
            obj->collideX(obj);
        }
        else
        {
            obj->collideX(shared_from_this());
            this->collideX(obj);
        }

//        if(obj->life_ == 1 && obj->typeOfObject == objectType::Pipe)
//        {
//            return true;
//        }
        if(obj->life_ == 1 && obj->typeOfObject == objectType::Turtle)
        {
//            std::cout << "return false?\n";
            return false;
        }

        return true;
    }
    return false;
}

bool Goomba::checkRight(std::shared_ptr<Object> obj, int dx_)
{
    if(checkYRange(obj) && checkXRight(obj) && (obj->dx_ < 0))
    {
        std::cout << "----------------------------------\n";
        std::cout << Object::getStringTypeOfObject(obj) << " hit right side of goomba\n";
        std::cout << "----------------------------------\n";
        if(obj->typeOfObject == objectType::Mario)
        {
            obj->collideX(obj);
        }
        else
        {
            obj->collideX(shared_from_this());
            this->collideX(obj);
        }

        if(obj->life_ == 1 && obj->typeOfObject == objectType::Turtle)
        {
//            std::cout << "return false?\n";
            return false;
        }

        return true;
    }
    return false;
}

bool Goomba::checkTop(std::shared_ptr<Object> obj, int dy_)
{
//    if((this->life_ == 0) && obj->type)

    if(checkYTop(obj) && checkXRange(obj))
    {
        std::cout << "----------------------------------\n";
        std::cout << Object::getStringTypeOfObject(obj) << " hit top side of goomba\n";
        std::cout << "----------------------------------\n";
//        obj->collideX(shared_from_this());
//        this->collideX(obj);
        this->stompY(obj);
        return true;
    }
    return false;
}

bool Goomba::checkBottom(std::shared_ptr<Object> obj, int dy_)
{
    if(checkYBottom(obj) && checkXRange(obj))
    {
        std::cout << "----------------------------------\n";
        std::cout << Object::getStringTypeOfObject(obj) << " hit bottom side of goomba\n";
        std::cout << "----------------------------------\n";
        return true;
    }
    return false;
}

void Goomba::moveYX()
{
    Object::moveY();
    Object::moveX();
}

const std::string Goomba::getStringTypeOfObject() const
{
    return std::string("Goomba");
}

void Goomba::decreaseLife()
{
    if(life_ > 0)
    {
        --life_;
        this->X_ = 2;
        if(life_ == 0) timeOfDeath = GetTickCount();
    }
    else if(life_ < 0) std::cout << "Goomba life <0, why?" << std::endl;
    else std::cout << "Someone tried to decreaseLife on a dead goomba, why and who?" << std::endl;
}

void Goomba::afterDraw()
{
//    if(timeOfDeath != 0)
//    {
//        std::cout << "diff: " << (GetTickCount() - timeOfDeath) << std::endl;
//        std::cout << "life_: " << life_ << std::endl;
//    }
    if((this->life_ == 1) &&(this->dx_ != 0))
    {
        Object::afterDraw();
    }
    else if((this->life_ < 1) && ((GetTickCount() - timeOfDeath) > 100))
    {
        std::cout << "removing dead goomba\n";
        this->removeDeadObject(shared_from_this());
        // do nothing
    }
}
