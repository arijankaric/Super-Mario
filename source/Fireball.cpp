#include "../include/Fireball.hpp"

Fireball::Fireball(int x, int y, int dx_, int dy_)
{
//    std::cout << "Making of fireball!!\n";
//    std::cout << "x: " << x << std::endl;
//    std::cout << "y: " << y << std::endl;
//    std::cout << "dx_: " << dx_ << std::endl;
//    std::cout << "dy_: " << dy_ << std::endl;
//    system("pause");

    this->hbm_ = this->hbmFireball_;
    this->hbmMask_ = this->hbmFireballMask_;
    this->maxCycles_ = 4;
    this->cyclesForChange = 3;
    this->typeOfObject = objectType::Fireball;
    GetObject(hbm_, sizeof(BITMAP), &bitmap);

    this->width = bitmap.bmWidth/4;
    this->height = bitmap.bmHeight;
    this->y = y;
    this->x = x;
    this->dx_ = dx_;
    this->dy_ = dy_;
    this->bottomSide = 12;
    this->leftSide = 0;
    this->rightSide = 7;
    this->topSide = 3;
    this->ground = 320;
    this->cyclesUntilDeath = -2;
    this->phases = true;
//    this->deadly = true;
}

bool Fireball::checkLeft(std::shared_ptr<Object> obj, int dx_)
{
    if(checkYRange(obj) && checkXLeft(obj) && (obj->dx_ > 0))
    {
        std::cout << "----------------------------------\n";
        std::cout << Object::getStringTypeOfObject(obj) << " hit left side of fireball\n";
        std::cout << "----------------------------------\n";
        obj->collideX(obj);
        return true;
    }
    return false;
}

bool Fireball::checkRight(std::shared_ptr<Object> obj, int dx_)
{
    if(checkYRange(obj) && checkXRight(obj) && (obj->dx_ < 0))
    {
        std::cout << "----------------------------------\n";
        std::cout << Object::getStringTypeOfObject(obj) << " hit right side of fireball\n";
        std::cout << "----------------------------------\n";
        obj->collideX(obj);
        return true;
    }
    return false;
}

bool Fireball::checkTop(std::shared_ptr<Object> obj, int dy_)
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

bool Fireball::checkBottom(std::shared_ptr<Object> obj, int dy_)
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


