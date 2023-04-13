#include "Pipe.hpp"

Pipe::Pipe(int x, int y)
{
//    this->objects = obj;
//    this->movingObjects = movObj;
    this->typeOfObject = objectType::Pipe;
    this->x = x;
    this->startingY = this->y = y;
    this->dy = 0;
    this->dx = 0;
    this->hbm_ = NULL; // don't animate, implement no animation
    this->hbmMask_ = NULL;
    this->max = 1;
    this->X = 0;
    this->leftSide = 17;
    this->rightSide = 48;
    this->topSide = -23;
    this->bottomSide = 25;
    this->moveable = false;
}

bool Pipe::checkLeft(std::shared_ptr<Object> obj, int dx)
{
    if(checkYRange(obj) && checkXLeft(obj) && (obj->dx > 0))
    {
        std::cout << "----------------------------------\n";
        std::cout << Object::getStringTypeOfObject(obj) << " hit left side of pipe\n";
        std::cout << "----------------------------------\n";
        this->collideX(obj);
        obj->collideX(shared_from_this());
        return true;
    }
    return false;
}

bool Pipe::checkRight(std::shared_ptr<Object> obj, int dx)
{
    if(checkYRange(obj) && checkXRight(obj) && (obj->dx < 0))
    {
        std::cout << "----------------------------------\n";
        std::cout << Object::getStringTypeOfObject(obj) << " hit right side of pipe\n";
        std::cout << "----------------------------------\n";
        this->collideX(obj);
        obj->collideX(shared_from_this());
        return true;
    }
    return false;
}

bool Pipe::checkTop(std::shared_ptr<Object> obj, int dy)
{
    if(checkYTop(obj) && checkXRange(obj))
    {
        obj->setYState(stateY::Neutral);
//        obj->dy = obj->testingY - obj->y;
        obj->ground = obj->testingY + obj->bottomSide;
        std::cout << "----------------------------------\n";
        std::cout << Object::getStringTypeOfObject(obj) << " hit top side of pipe\n";
        std::cout << "----------------------------------\n";
        return true;
    }
    return false;
}

bool Pipe::checkBottom(std::shared_ptr<Object> obj, int dy)
{
    if(checkYBottom(obj) && checkXRange(obj))
    {
        std::cout << "----------------------------------\n";
        std::cout << Object::getStringTypeOfObject(obj) << " hit bottom side of pipe\n";
        std::cout << "----------------------------------\n";
        return true;
    }
    return false;
}

void Pipe::moveYX()
{
    // pipe se ne krece
}

void Pipe::moveY()
{

}

void Pipe::moveX()
{

}

const std::string Pipe::getStringTypeOfObject() const
{
    return std::string("Pipe");
}

void Pipe::collideX(std::shared_ptr<Object> obj)
{
    return;
}

