#include "../include/Turtle.hpp"

Turtle::Turtle(int x, int y)
{
//    this->objects = obj;
//    this->movingObjects = movObj;
    this->life_ = 2;
    this->hbm_ = left;
    this->hbmMask_ = leftMask;
    std::cout << "hbm: " << hbm_ << std::endl;
    std::cout << "hbmMask_: " << hbmMask_ << std::endl;
    this->maxCycles_ = 2;
    this->cyclesForChange = 3;
    this->typeOfObject = objectType::Turtle;
    GetObject(hbm_, sizeof(BITMAP), &bitmap);

    this->width = bitmap.bmWidth/6;
    this->height = bitmap.bmHeight;
    this->y = y;
    this->x = x;
    this->dx_ = 1;
    this->dy_ = 0;
    this->bottomSide = 28;
    this->leftSide = 0;
    this->rightSide = 15;
    this->topSide = 2;
    this->ground = 320;
    this->moveable = true;
//    this->deadly = true;
}

bool Turtle::checkLeft(std::shared_ptr<Object> obj, int dx_)
{
    if(checkYRange(obj) && checkXLeft(obj) && (obj->dx_ > 0))
    {
        std::cout << "----------------------------------\n";
        std::cout << Object::getStringTypeOfObject(obj) << " hit left side of turtle\n";
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

        if(this->life_ == 1 && obj->typeOfObject == objectType::Pipe)
        {
            return true;
        }
        else if(this->life_ == 1)
        {
            std::cout << "return false?\n";
            return false;
        }

        return true;
    }
    if(checkLeftEdge(obj))
    {
        std::cout << "----------------------------------\n";
        std::cout << Object::getStringTypeOfObject(obj) << " hit left edge of turtle\n";
        std::cout << "----------------------------------\n";
//        obj->collideX(shared_from_this());
        this->collideX(obj);
        return true;
    }
    return false;
}

bool Turtle::checkRight(std::shared_ptr<Object> obj, int dx_)
{
    if(checkYRange(obj) && checkXRight(obj) && (obj->dx_ < 0))
    {
        std::cout << "----------------------------------\n";
        std::cout << Object::getStringTypeOfObject(obj) << " hit right side of turtle\n";
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

        if(this->life_ == 1 && obj->typeOfObject == objectType::Pipe)
        {
            return true;
        }
        else if(this->life_ == 1)
        {
            return false;
        }

        return true;
    }
    if(checkRightEdge(obj))
    {
        std::cout << "----------------------------------\n";
        std::cout << Object::getStringTypeOfObject(obj) << " hit right edge of turtle\n";
        std::cout << "----------------------------------\n";
//        obj->collideX(shared_from_this());
        this->collideX(obj);
        return true;
    }
    return false;
}

bool Turtle::checkTop(std::shared_ptr<Object> obj, int dy_)
{
    static bool hit = false;
    static DWORD timeOfHit = GetTickCount();
    if(checkYTop(obj) && checkXRange(obj) && (obj->dy_ >= 0))
    {
        if(hit || (GetTickCount() - timeOfHit) < 100)
        {
            std::cout << "----------------------------------\n";
            std::cout << Object::getStringTypeOfObject(obj) << " standing on top side of turtle\n";
            std::cout << "----------------------------------\n";
//            this->stompY(obj);
        }
        else
        {
            std::cout << "----------------------------------\n";
            std::cout << Object::getStringTypeOfObject(obj) << " hit top side of turtle\n";
            std::cout << "----------------------------------\n";
            timeOfHit = GetTickCount();
            this->stompY(obj);
        }

        if(obj->typeOfObject == objectType::Mario)
        {
            obj->setYState(stateY::Neutral);
        }
        obj->ground = obj->testingY + obj->bottomSide;
        hit = true;
        return true;
    }
    hit = false;
    return false;
}

bool Turtle::checkBottom(std::shared_ptr<Object> obj, int dy_)
{
    if(checkYBottom(obj) && checkXRange(obj) && (obj->dy_ < 0))
    {
        std::cout << "----------------------------------\n";
        std::cout << Object::getStringTypeOfObject(obj) << " hit bottom side of turtle\n";
        std::cout << "----------------------------------\n";
        return true;
    }
    return false;
}

const std::string Turtle::getStringTypeOfObject() const
{
    return std::string("Turtle");
}

void Turtle::increaseLife()
{
    ++life_;
    if(life_ == 2)
    {
        this->height = this->height * 2;
        this->Y_ = 0;
        this->X_ = 0;
        this->maxCycles_ = 2;
        this->dx_ = 1;
        this->y -= 13;
        this->bottomSide += 13;
        this->topSide += 3;
    }
}

void Turtle::decreaseLife()
{
    if(life_ == 2)
    {
        --life_;
        this->height = this->height / 2;
        this->Y_ = 0;
        this->X_ = 2;
        this->maxCycles_ = 6;
        this->y += 13;
        this->bottomSide -= 13;
        this->dx_ = 0;
        this->topSide -= 3;
        this->timeOfDeath = GetTickCount();
    }
    else
    {
        return;
        // fireball for the kill? implement later
    }
}

void Turtle::draw(HDC hdcBuffer, HDC hdcMem)
{
    if(this->dx_ > 0)
    {
        hbm_ = right;
        hbmMask_ = rightMask;
    }
    else if(this->dx_ < 0)
    {
        hbm_ = left;
        hbmMask_ = leftMask;
    }
    else
    {
//        std::cout << "Turtle dx_ = 0, why? Because life == 1, that's why\n";
    }

    Object::draw(hdcBuffer, hdcMem);
}

void Turtle::afterDraw()
{
//    std::cout << "this->life_: " << this->life_ << std::endl;
    if(this->x < 0  || this->y > VISINAPROZORA * 2)
    {
        this->removeDeadObject(shared_from_this());
        return;
    }

    if(this->life_ == 2)
    {
        Object::afterDraw();
    }
    else if((this->life_ == 1))
    {
        if(this->dx_ == 0)
        {
            if((GetTickCount() - this->timeOfDeath) > 2500)
            {
                this->increaseLife();
            }
            else if((GetTickCount() - this->timeOfDeath) > 1500)
            {
//                std::cout << "turtle->Y: " << this->Y_ << std::endl;
                if(++this->changeCycles == this->cyclesForChange)
                {
                    ++this->Y_;
                    this->changeCycles = 0;
                }
                this->Y_ = this->Y_%2;
            }
        }
        else
        {
            this->Y_ = 0;
            if(++this->changeCycles == this->cyclesForChange)
            {
                ++this->X_;
                this->changeCycles = 0;
            }

            if(this->X_ >= this->maxCycles_)
            {
                this->X_ = 2;
            }
        }
    }
    else if(this->life_ == 0)
    {
        std::cout << "Turtle dead?\n";
    }
}

void Turtle::stompY(std::shared_ptr<Object> obj)
{
    if((life_ == 1) && (obj->typeOfObject == objectType::Mario) && (this->dx_ == 0))
    {
        std::cout << "Turte go on rampage\n";
        if(this->centerX() < obj->centerX())
        {
            this->dx_ = -7;
        }
        else
        {
            this->dx_ = 7;
        }
    }
    else if((life_ == 1) && (obj->typeOfObject == objectType::Mario) && (this->dx_ != 0))
    {
        std::cout << "Turte stop rampaging\n";
        this->dx_ = 0;
    }

    Object::stompY(obj);
}

void Turtle::collideX(std::shared_ptr<Object> obj)
{
    std::cout << "Turtle collided with: " << obj->getStringTypeOfObject() << std::endl;
    if(life_ == 1 && this->dx_ != 0 && obj->moveable)
    {
        std::cout << "Turtle killed " << obj->getStringTypeOfObject() << std::endl;
        return;
    }
    else
    {
        Object::collideX(obj);
        return;
    }
}



