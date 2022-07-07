#include "FlowerEnemy.hpp"

FlowerEnemy::FlowerEnemy(vektorObjekata obj, vektorObjekata movObj, int x, int y)
{
    this->objects = obj;
    this->movingObjects = movObj;
    this->typeOfObject = FLOWER_ENEMY;
    this->x = x;
    this->startingY = this->y = y;
    this->dy = -3;
    this->hbm_ = enemy;
    this->hbmMask_ = enemyMask;
    GetObject(this->hbm_, sizeof(BITMAP), &bitmap);
    this->width = bitmap.bmWidth/6;
    this->height = bitmap.bmHeight;
    this->max = 2;
    this->X = 0;
    this->leftSide = -1;
    this->rightSide = 17;
    this->topSide = -1;
    this->bottomSide = 35;
    this->cyclesForChange = 10;
//    this->parent = p;
//    this->changeCycles = 0;
    if(outline)
        this->outline = true;
}

bool FlowerEnemy::checkBottom(std::shared_ptr<Object> obj)
{

    if((this->flag == true) && ((obj->x + obj->leftSide) < (this->x + this->rightSide)) && ((obj->x + obj->rightSide) > (this->x + this->leftSide)) && ((obj->testingY + obj->topSide) == (this->y + this->bottomSide)))
    {
        std::cout << getStringTypeOfObject(obj) << " hit flower_enemy bottom side(why?)\n";
//        praviUpdate(hwnd);
//        Render(hwnd);
        system("pause");
        return false;
    }
    return true;
}

bool FlowerEnemy::checkTop(std::shared_ptr<Object> obj)
{
    if((this->flag == true) && (obj->stateY != UP) && ((obj->x + obj->leftSide) < (this->x + this->rightSide)) && ((obj->x + obj->rightSide) > (this->x + this->leftSide)) && ((obj->testingY + obj->bottomSide) == (this->y + this->topSide)))
    {
        obj->dy = obj->y - obj->testingY;
        std::cout << getStringTypeOfObject(obj) << " hit flower_enemy top side" << std::endl;
//        praviUpdate(hwnd);
//        Render(hwnd);
        system("pause");
        return false;
    }
    return true;
}

bool FlowerEnemy::checkLeft(std::shared_ptr<Object> obj)
{
    if(((obj->x + obj->rightSide) == (this->x + this->leftSide)) && (((obj->y + obj->bottomSide) < (this->y + this->bottomSide)) && ((obj->y + obj->bottomSide) > (this->y + this->topSide)) || ((obj->y + obj->topSide) <= (this->y + this->bottomSide)) && ((obj->y + obj->topSide) > (this->y + this->topSide))))
    {
        std::cout << "----------------------------------\n";
        std::cout << getStringTypeOfObject(obj) << " hit left side of flower_enemy\n";
        std::cout << "----------------------------------\n";
        system("pause");
        return false;
    }
    return true;

}

bool FlowerEnemy::checkRight(std::shared_ptr<Object> obj)
{
    if(((obj->x + obj->leftSide) == (this->x + this->rightSide)) && (((obj->y + obj->bottomSide) < (this->y + this->bottomSide)) && ((obj->y + obj->bottomSide) > (this->y + this->topSide)) || ((obj->y + obj->topSide) <= (this->y + this->bottomSide)) && ((obj->y + obj->topSide) > (this->y + this->topSide))))
    {
        std::cout << "----------------------------------\n";
        std::cout << getStringTypeOfObject(obj) << " hit right side of flower_enemy\n";
        std::cout << "----------------------------------\n";
        system("pause");
        return false;
    }
    return true;
}

void FlowerEnemy::draw(HDC hdcBuffer, HDC hdcMem)
{
    int height = this->startingY - this->y;
    SelectObject(hdcMem, this->hbm_);
    BitBlt(hdcBuffer, this->x, this->y, this->width, height, hdcMem, this->X*this->width, 0, SRCAND);

    SelectObject(hdcMem, this->hbmMask_);
    BitBlt(hdcBuffer, this->x, this->y, this->width, height, hdcMem, this->X*this->width, 0, SRCPAINT);

    return;
}
