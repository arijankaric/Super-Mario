#include "FlowerEnemy.hpp"

FlowerEnemy::FlowerEnemy(int x, int y, TIMERPROC upFunc, TIMERPROC downFunc)
{
    this->upFunc_ = upFunc;
    this->downFunc_ = downFunc;
//    this->objects = obj;
//    this->movingObjects = movObj;
    this->typeOfObject = objectType::FlowerEnemy;
    this->x = x;
    this->startingY = this->y = y;
    this->dy = -3;
    this->hbm_ = left;
    this->hbmMask_ = leftMask;
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

FlowerEnemy::FlowerEnemy(int x, int y, std::shared_ptr<Object> parentPipe, flowerType choice)
{
//    this->objects = obj;
//    this->movingObjects = movObj;
//    std::cout << "flower mask: " << leftMask << " nonmask: " << left << std::endl;
//    system("pause");
    this->parentPipe_ = parentPipe;
    this->typeOfObject = objectType::FlowerEnemy;
    this->x = x;
    this->startingY = this->y = y;
    this->dy = -3;
    this->hbm_ = left;
    this->hbmMask_ = leftMask;
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
    this->typeOfFlowerEnemy = choice;

//    this->parent = p;
//    this->changeCycles = 0;
}

bool FlowerEnemy::checkBottom(std::shared_ptr<Object> obj, int dy)
{

    if((this->flag == true) && ((obj->x + obj->leftSide) < (this->x + this->rightSide)) && ((obj->x + obj->rightSide) > (this->x + this->leftSide)) && ((obj->testingY + obj->topSide) == (this->y + this->bottomSide)))
    {
        std::cout << Object::getStringTypeOfObject(obj) << " hit flower_enemy bottom side(why?)\n";
//        praviUpdate(hwnd);
//        Render(hwnd);
        system("pause");
        return true;
    }
    return false;
}

bool FlowerEnemy::checkTop(std::shared_ptr<Object> obj, int dy)
{
    if((this->flag == true) && (obj->stY_ != Object::stateY::Up) && ((obj->x + obj->leftSide) < (this->x + this->rightSide)) && ((obj->x + obj->rightSide) > (this->x + this->leftSide)) && ((obj->testingY + obj->bottomSide) == (this->y + this->topSide)))
    {
        obj->dy = obj->y - obj->testingY;
        std::cout << Object::getStringTypeOfObject(obj) << " hit flower_enemy top side" << std::endl;
//        praviUpdate(hwnd);
//        Render(hwnd);
        obj->collideX(shared_from_this());
        this->collideX(obj);
        return true;
    }
    return false;
}

bool FlowerEnemy::checkLeft(std::shared_ptr<Object> obj, int dx)
{
    if(checkYRange(obj) && checkXLeft(obj) && (obj->dx > 0) && obj->typeOfObject == objectType::Mario)
    {
        std::cout << "----------------------------------\n";
        std::cout << Object::getStringTypeOfObject(obj) << " hit left side of flower_enemy\n";
        std::cout << "----------------------------------\n";
        obj->collideX(shared_from_this());
        this->collideX(obj);
        return true;
    }
    return false;
}

bool FlowerEnemy::checkRight(std::shared_ptr<Object> obj, int dx)
{
    if(checkYRange(obj) && checkXRight(obj) && (obj->dx < 0) && obj->typeOfObject == objectType::Mario)
    {
        std::cout << "----------------------------------\n";
        std::cout << Object::getStringTypeOfObject(obj) << " hit right side of flower_enemy\n";
        std::cout << "----------------------------------\n";
        obj->collideX(shared_from_this());
        this->collideX(obj);
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

void FlowerEnemy::afterDraw()
{
    if(this->typeOfFlowerEnemy == flowerType::eater)
    {
        Object::afterDraw();
    }
    else
    {
        // do nothing I guess, handle in trough/crest(up/down) function
    }
}

void FlowerEnemy::moveYX()
{
    static DWORD vrijeme_pocetak;
//    std::cout << "piranha->dy: " << this->dy << std::endl;
    if(this->y < this->startingY - 38)
    {
        std::cout << "flower_enemy reached peak " << mario->y << std::endl;
//        HWND hwnd = GetForegroundWindow();
        this->dy = 0;
        this->y = this->startingY - 38;
        vrijeme_pocetak = GetTickCount();
//        SetTimer(hwnd, (UINT_PTR)this, 3000, upFunc_);
//        std::cout << "UpTimer" << std::endl;

        if(typeOfFlowerEnemy == flowerType::thrower)
        {
            std::cout << "new fireball in direction x: " << this->direction_.first << " direction y: " << this->direction_.second << std::endl;
            objects->push_back(std::make_shared<Fireball>(this->x + this->leftSide, this->y + this->topSide, this->direction_.first, this->direction_.second));
        }

    }

    else if((this->y == this->startingY - 38) && ((GetTickCount() - vrijeme_pocetak) > 3000))
    {
        this->dy = 3;
    }
    else if(this->y > this->startingY)
    {
        std::cout << "flower_enemy reached through " << mario->y << std::endl;
//        HWND hwnd = GetForegroundWindow();
        this->dy = 0;
        this->y = this->startingY;
        this->flag = false; // piranha is not active
        vrijeme_pocetak = GetTickCount();
//        SetTimer(hwnd, (UINT_PTR)this, 4500, downFunc_);
//        std::cout << "DownTimer" << std::endl;


    }
    else if((this->y == this->startingY) && ((GetTickCount() - vrijeme_pocetak) > 3000) && (mario->ground != this->parentPipe_->getTop()) && (distanceBetweenObjects(mario.get(), this->parentPipe_.get()) > 80))
    {
        std::cout << "distance between parent pipe and mario: " << distanceBetweenObjects(mario.get(), this->parentPipe_.get()) << std::endl;
        if(this->typeOfFlowerEnemy == flowerType::thrower)
        {
            const unsigned int quadrant = this->determineQuadrant();
            this->getDirection(quadrant);
        }
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
        if((this->flag == true) && (mario->stY_ != stateY::Down) && ((mario->x + mario->leftSide) < (this->x + this->rightSide)) && ((mario->x + mario->rightSide) > (this->x + this->leftSide)) && ((mario->y + mario->bottomSide) == (this->testingY + this->topSide)))
        {
            std::cout << "Mario hit flower_enemy top side: " << mario->y << " " << (this->testingY + this->topSide) << std::endl;
            mario->flag = true;
            system("pause");
            break;
        }
        else if((this->flag == true) && ((mario->x + mario->leftSide) < (this->x + this->rightSide)) && ((mario->x + mario->rightSide) > (this->x + this->leftSide)) && ((mario->y + mario->topSide) == (this->testingY + this->bottomSide)))
        {
            std::cout << "Mario hit flower_enemy bottom side(why?)\n";
            mario->flag = true;
            system("pause");
            break;
        }
        this->testingY += directionY;
    }

    this->moveY();
    this->moveX();
}

void FlowerEnemy::moveY()
{
    this->y += (this->testingY - this->y);
}
void FlowerEnemy::moveX()
{
    this->x += this->dx;
}

const std::string FlowerEnemy::getStringTypeOfObject() const
{
    return std::string("FlowerEnemy");
}

void FlowerEnemy::getDirection(int quadrant)
{
    switch(quadrant)
    {
    case 1:
        this->X = 5;
        this->hbm_ = right;
        this->hbmMask_ = right;
        this->direction_ = std::pair<int, int>(1, -1);
        break;
    case 2:
        this->X = 5;
        this->hbm_ = left;
        this->hbmMask_ = left;
        this->direction_ = std::pair<int, int>(-1, -1);
        break;
    case 3:
        this->X = 3;
        this->hbm_ = left;
        this->hbmMask_ = leftMask;
        this->direction_ = std::pair<int, int>(-1, 1);
        break;
    case 4:
        this->X = 3;
        this->hbm_ = right;
        this->hbmMask_ = rightMask;
        this->direction_ = std::pair<int, int>(1, 1);
        break;
    default:
        std::cout << "This shouldn't happen. Quadrant: " << quadrant << std::endl;
        system("pause");
    }
}
