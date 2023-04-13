#include "Fireball.hpp"

Fireball::Fireball(int x, int y, int dx, int dy)
{
//    std::cout << "Making of fireball!!\n";
//    std::cout << "x: " << x << std::endl;
//    std::cout << "y: " << y << std::endl;
//    std::cout << "dx: " << dx << std::endl;
//    std::cout << "dy: " << dy << std::endl;
//    system("pause");
    this->hbm_ = (HBITMAP) LoadImage(NULL, "fireball.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    this->hbmMask_ = (HBITMAP) LoadImage(NULL, "fireballBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    this->max = 4;
    this->cyclesForChange = 3;
    this->typeOfObject = objectType::Fireball;
    GetObject(hbm_, sizeof(BITMAP), &bitmap);

    this->width = bitmap.bmWidth/4;
    this->height = bitmap.bmHeight;
    this->y = y;
    this->x = x;
    this->dx = dx;
    this->dy = dy;
    this->bottomSide = 12;
    this->leftSide = 0;
    this->rightSide = 7;
    this->topSide = 3;
    this->ground = 320;
    this->cyclesUntilDeath = -2;
//    this->deadly = true;
}

bool Fireball::checkLeft(std::shared_ptr<Object> obj, int dx)
{
    if(checkYRange(obj) && checkXLeft(obj) && (obj->dx > 0))
    {
        std::cout << "----------------------------------\n";
        std::cout << Object::getStringTypeOfObject(obj) << " hit left side of fireball\n";
        std::cout << "----------------------------------\n";
        obj->collideX(obj);
        return true;
    }
    return false;
}

bool Fireball::checkRight(std::shared_ptr<Object> obj, int dx)
{
    if(checkYRange(obj) && checkXRight(obj) && (obj->dx < 0))
    {
        std::cout << "----------------------------------\n";
        std::cout << Object::getStringTypeOfObject(obj) << " hit right side of fireball\n";
        std::cout << "----------------------------------\n";
        obj->collideX(obj);
        return true;
    }
    return false;
}

bool Fireball::checkTop(std::shared_ptr<Object> obj, int dy)
{
    if(checkYTop(obj) && checkXRange(obj))
    {
        std::cout << "----------------------------------\n";
        std::cout << Object::getStringTypeOfObject(obj) << " hit top side of fireball\n";
        std::cout << "----------------------------------\n";
        return true;
    }
    return false;
}

bool Fireball::checkBottom(std::shared_ptr<Object> obj, int dy)
{
    if(checkYBottom(obj) && checkXRange(obj))
    {
        std::cout << "----------------------------------\n";
        std::cout << Object::getStringTypeOfObject(obj) << " hit bottom side of fireball\n";
        std::cout << "----------------------------------\n";
        return true;
    }
    return false;
}

const std::string Fireball::getStringTypeOfObject() const
{
    return std::string("Fireball");
}


