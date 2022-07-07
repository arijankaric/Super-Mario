#include "Ground.hpp"

Ground::Ground(int x, int y)
{
    this->typeOfObject = GROUND;
    this->x = this->startingX = x;
    this->startingY = this->y = y;
    this->dy = 0;
    this->dx = 0;
    this->hbm_ = ground;
    this->hbmMask_ = groundMask;
    GetObject(this->hbm_, sizeof(BITMAP), &bitmap);
    this->width = bitmap.bmWidth;
    this->height = bitmap.bmHeight;
    this->max = 1;
    this->X = 0;
    this->bottomSide = 20;
    this->topSide = 0;
    this->leftSide = 0;
    this->rightSide = 53;
//    this->changeCycles = 0;
}

bool Ground::checkBottom(std::shared_ptr<Object> obj)
{
    if(((obj->x + obj->leftSide) < (this->x + this->rightSide)) && ((obj->x + obj->rightSide) > (this->x + this->leftSide)) && ((obj->testingY + obj->topSide) == (this->y + this->bottomSide)))
    {
        std::cout << getStringTypeOfObject(obj) << " hit bottom of ground" << std::endl;
        obj->stateY = DOWN;
        obj->dy = (obj->y - obj->testingY - 2);
//                praviUpdate(hwnd);
//                Render(hwnd);
//                obj->dy = -5;
//                system("pause");
        return false;
    }
    return true;
}

bool Ground::checkTop(std::shared_ptr<Object> obj)
{
    if(((obj->x + obj->leftSide) < (this->x + this->rightSide)) && ((obj->x + obj->rightSide) > (this->x + this->leftSide)) && ((obj->testingY + obj->bottomSide) == (this->y + this->topSide)))
    {
        std::cout << getStringTypeOfObject(obj) << "hit top of ground" << std::endl;
        obj->dy = (obj->y - obj->testingY);
        obj->ground = obj->testingY + obj->bottomSide;
        obj->objectY = 1;
        return false;
    }
    return true;
}

bool Ground::checkLeft(std::shared_ptr<Object> obj)
{
    if(((obj->x + obj->rightSide) == (this->x + this->leftSide)) && (((obj->y + obj->bottomSide) <= (this->y + this->bottomSide)) && ((obj->y + obj->bottomSide) > (this->y + this->topSide)) || ((obj->y + obj->topSide) <= (this->y + this->bottomSide)) && ((obj->y + obj->topSide) > (this->y + this->topSide))))
    {
        std::cout << "----------------------------------\n";
        std::cout << getStringTypeOfObject(obj) << " hit left side of ground\n";
        std::cout << "----------------------------------\n";
        return false;
    }
    return true;
}

bool Ground::checkRight(std::shared_ptr<Object> obj)
{
    if(((obj->x + obj->leftSide) == (this->x + this->rightSide)) && (((obj->y + obj->bottomSide) < (this->y + this->bottomSide)) && ((obj->y + obj->bottomSide) > (this->y + this->topSide)) || ((obj->y + obj->topSide) <= (this->y + this->bottomSide)) && ((obj->y + obj->topSide) > (this->y + this->topSide))))
    {
        std::cout << "----------------------------------\n";
        std::cout << getStringTypeOfObject(obj) << " hit right side of ground\n";
        std::cout << "----------------------------------\n";
        return false;
    }
    return true;
}

