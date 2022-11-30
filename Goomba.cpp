#include "Goomba.hpp"

Goomba::Goomba(int x, int y)
{
    this->typeOfObject = objectType::Goomba;
//    this->objects = obj;
//    this->movingObjects = movObj;
    this->hbm_ = (HBITMAP) LoadImage(NULL, "goomba.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    this->hbmMask_ = (HBITMAP) LoadImage(NULL, "goombaBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    this->max = 2;
    this->cyclesForChange = 3;
    GetObject(hbm_, sizeof(BITMAP), &bitmap);

    this->width = bitmap.bmWidth/4;
    this->height = bitmap.bmHeight;
    this->y = y;
    this->x = x;
    this->dx = -1;
    this->dy = 0;
    this->bottomSide = 15;
    this->leftSide = 0;
    this->rightSide = 15;
    this->topSide = 0;
    this->ground = 320;
    this->moveable = true;
}

bool Goomba::checkLeft(std::shared_ptr<Object> obj, int dx)
{
    if(checkYRange(obj) && checkXLeft(obj) && (obj->dx > 0))
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

bool Goomba::checkRight(std::shared_ptr<Object> obj, int dx)
{
    if(checkYRange(obj) && checkXRight(obj) && (obj->dx < 0))
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

bool Goomba::checkTop(std::shared_ptr<Object> obj, int dy)
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

bool Goomba::checkBottom(std::shared_ptr<Object> obj, int dy)
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
        this->X = 2;
        timeOfDeath = GetTickCount();
    }
}

void Goomba::afterDraw()
{
//    if(timeOfDeath != 0)
//    {
//        std::cout << "diff: " << (GetTickCount() - timeOfDeath) << std::endl;
//        std::cout << "life_: " << life_ << std::endl;
//    }
    if((this->life_ == 1) &&(this->dx != 0))
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
