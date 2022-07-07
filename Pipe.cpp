#include "Pipe.hpp"

Pipe::Pipe(int x, int y, vektorObjekata obj, vektorObjekata movObj)
{
    this->objects = obj;
    this->movingObjects = movObj;
    this->typeOfObject = PIPE;
    this->x = x;
    this->startingY = this->y = y;
    this->dy = 0;
    this->hbm_ = NULL; // don't animate, implement no animation
    this->hbmMask_ = NULL;
    this->max = 1;
    this->X = 0;
    this->leftSide = 17;
    this->rightSide = 48;
    this->topSide = -23;
    this->bottomSide = 25;
    if(outline)
        this->outline = true;
}

bool Pipe::checkLeft(std::shared_ptr<Object> obj)
{
    if(((obj->x + obj->rightSide) == (this->x + this->leftSide)) && (((obj->y + obj->bottomSide) <= (this->y + this->bottomSide)) && ((obj->y + obj->bottomSide) > (this->y + this->topSide)) || ((obj->y + obj->topSide) <= (this->y + this->bottomSide)) && ((obj->y + obj->topSide) > (this->y + this->topSide))))
    {
        std::cout << "----------------------------------\n";
        std::cout << getStringTypeOfObject(obj) << " hit left side of pipe\n";
        std::cout << "----------------------------------\n";
        return false;
    }
    return true;
}

bool Pipe::checkRight(std::shared_ptr<Object> obj)
{
    if(((obj->x + obj->leftSide) == (this->x + this->rightSide)) && (((obj->y + obj->bottomSide) < (this->y + this->bottomSide)) && ((obj->y + obj->bottomSide) > (this->y + this->topSide)) || ((obj->y + obj->topSide) <= (this->y + this->bottomSide)) && ((obj->y + obj->topSide) > (this->y + this->topSide))))
    {
        std::cout << "----------------------------------\n";
        std::cout << getStringTypeOfObject(obj) << " hit right side of pipe\n";
        std::cout << "----------------------------------\n";
        return false;
    }
    return true;
}

bool Pipe::checkTop(std::shared_ptr<Object> obj)
{
    return true;
}

bool Pipe::checkBottom(std::shared_ptr<Object> obj)
{
    return true;
}
