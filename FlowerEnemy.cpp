#include "FlowerEnemy.hpp"

FlowerEnemy::FlowerEnemy(vektorObjekata obj, vektorObjekata movObj, int x, int y, TIMERPROC upFunc, TIMERPROC downFunc)
{
    this->upFunc_ = upFunc;
    this->downFunc_ = downFunc;
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
    this->cyclesForChange = 14;
//    this->parent = p;
//    this->changeCycles = 0;
}

bool FlowerEnemy::checkBottom(std::shared_ptr<Object> obj, int dy)
{

    if((this->flag == true) && ((obj->x + obj->leftSide) < (this->x + this->rightSide)) && ((obj->x + obj->rightSide) > (this->x + this->leftSide)) && ((obj->testingY + obj->topSide) == (this->y + this->bottomSide)))
    {
        std::cout << getStringTypeOfObject(obj) << " hit flower_enemy bottom side(why?)\n";
//        praviUpdate(hwnd);
//        Render(hwnd);
        system("pause");
        return true;
    }
    return false;
}

bool FlowerEnemy::checkTop(std::shared_ptr<Object> obj, int dy)
{
    if((this->flag == true) && (obj->stateY != UP) && ((obj->x + obj->leftSide) < (this->x + this->rightSide)) && ((obj->x + obj->rightSide) > (this->x + this->leftSide)) && ((obj->testingY + obj->bottomSide) == (this->y + this->topSide)))
    {
        obj->dy = obj->y - obj->testingY;
        std::cout << getStringTypeOfObject(obj) << " hit flower_enemy top side" << std::endl;
//        praviUpdate(hwnd);
//        Render(hwnd);
        system("pause");
        return true;
    }
    return false;
}

bool FlowerEnemy::checkLeft(std::shared_ptr<Object> obj)
{
    if(((obj->x + obj->rightSide) == (this->x + this->leftSide)) && (((obj->y + obj->bottomSide) < (this->y + this->bottomSide)) && ((obj->y + obj->bottomSide) > (this->y + this->topSide)) || ((obj->y + obj->topSide) <= (this->y + this->bottomSide)) && ((obj->y + obj->topSide) > (this->y + this->topSide))))
    {
        std::cout << "----------------------------------\n";
        std::cout << getStringTypeOfObject(obj) << " hit left side of flower_enemy\n";
        std::cout << "----------------------------------\n";
        system("pause");
        return true;
    }
    return false;

}

bool FlowerEnemy::checkRight(std::shared_ptr<Object> obj)
{
    if(((obj->x + obj->leftSide) == (this->x + this->rightSide)) && (((obj->y + obj->bottomSide) < (this->y + this->bottomSide)) && ((obj->y + obj->bottomSide) > (this->y + this->topSide)) || ((obj->y + obj->topSide) <= (this->y + this->bottomSide)) && ((obj->y + obj->topSide) > (this->y + this->topSide))))
    {
        std::cout << "----------------------------------\n";
        std::cout << getStringTypeOfObject(obj) << " hit right side of flower_enemy\n";
        std::cout << "----------------------------------\n";
        system("pause");
        return true;
    }
    return false;
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

void FlowerEnemy::moveYX(std::shared_ptr<Object> obj, bool whosMoving)
{
    static DWORD vrijeme_pocetak;
//    std::cout << "piranha->dy: " << this->dy << std::endl;
    if(this->y < this->startingY - 38)
    {
        std::cout << "flower_enemy reached peak" << std::endl;
        HWND hwnd = GetForegroundWindow();
        this->dy = 0;
        this->y = this->startingY - 38;
        vrijeme_pocetak = GetTickCount();
//        SetTimer(hwnd, (UINT_PTR)this, 3000, upFunc_);
//        std::cout << "UpTimer" << std::endl;
    }
    else if((this->y == this->startingY - 38) && ((GetTickCount() - vrijeme_pocetak) > 3000))
    {
        this->dy = 3;
    }
    else if(this->y > this->startingY)
    {
        std::cout << "flower_enemy reached through" << std::endl;
        HWND hwnd = GetForegroundWindow();
        this->dy = 0;
        this->y = this->startingY;
        this->flag = false; // piranha is not active
        vrijeme_pocetak = GetTickCount();
//        SetTimer(hwnd, (UINT_PTR)this, 4500, downFunc_);
//        std::cout << "DownTimer" << std::endl;
    }
    else if((this->y == this->startingY) && ((GetTickCount() - vrijeme_pocetak) > 3000))
    {
        this->dy = -3;
    }

    this->testingY = this->y;
    int directionY;
    if(this->dy == 0)
        directionY = 0;
    else
        directionY = this->dy/abs(this->dy);
    int endPointY = this->y + this->dy;
    while(this->testingY != endPointY)
    {
        if((this->flag == true) && (obj->stateY != UP) && ((obj->x + obj->leftSide) < (this->x + this->rightSide)) && ((obj->x + obj->rightSide) > (this->x + this->leftSide)) && ((obj->y + obj->bottomSide) == (this->testingY + this->topSide)))
        {
            std::cout << "Mario hit flower_enemy top side: " << obj->y << " " << (this->testingY + this->topSide) << std::endl;
            obj->flag = true;
            system("pause");
            break;
        }
        else if((this->flag == true) && ((obj->x + obj->leftSide) < (this->x + this->rightSide)) && ((obj->x + obj->rightSide) > (this->x + this->leftSide)) && ((obj->y + obj->topSide) == (this->testingY + this->bottomSide)))
        {
            std::cout << "Mario hit flower_enemy bottom side(why?)\n";
            obj->flag = true;
            system("pause");
            break;
        }
        this->testingY += directionY;
    }

    this->moveY(obj, whosMoving);
    this->moveX(obj, whosMoving);
}
void FlowerEnemy::moveY(std::shared_ptr<Object> obj, bool whosMoving)
{
    this->y += (this->testingY - this->y);
}
void FlowerEnemy::moveX(std::shared_ptr<Object> obj, bool whosMoving)
{
    this->x += this->dx;
}
