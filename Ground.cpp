#include "Ground.hpp"

Ground::Ground(int x, int y, int falseGround)
{
    this->typeOfObject = objectType::Ground;
    this->x = this->startingX = x;
    this->startingY = this->y = y;
    this->dy = 0;
    this->dx = 0;
    this->hbm_ = ground;
    this->hbmMask_ = ground;
    GetObject(this->hbm_, sizeof(BITMAP), &bitmap);
    this->width = bitmap.bmWidth;
    this->height = bitmap.bmHeight;
    this->max = 1;
    this->X = 0;
    this->bottomSide = 20;
    this->topSide = 0;
    this->leftSide = 0;
    this->rightSide = 53;
    this->falseGround = falseGround;
//    this->changeCycles = 0;
}

bool Ground::checkBottom(std::shared_ptr<Object> obj, int dy)
{
    if(falseGround)
    {
        return false;
    }

    if(obj->typeOfObject == this->objectType::Fireball)
    {
        return false;
    }

//    std::cout << "Ground::checkBottom obj->dy: " << obj->dy << " proslijedjeni dy: " << dy << std::endl;
    if(checkYBottom(obj) && checkXRange(obj) && (dy < 0))
    {
//        std::cout << Object::getStringTypeOfObject(obj) << " hit bottom of ground" << std::endl;
        obj->setYState(stateY::Down);
//        ++(obj->testingY);
//        obj->dy = (obj->testingY - obj->y + 1);
//                praviUpdate(hwnd);
//                Render(hwnd);
//                obj->dy = -5;
//                system("pause");
        return true;
    }
    return false;
}

bool Ground::checkTop(std::shared_ptr<Object> obj, int dy)
{
    if(obj->typeOfObject == this->objectType::Fireball)
    {
        return false;
    }

//    std::cout << obj->y + obj->bottomSide << " " << this->y + this->topSide << " " << checkYTop(obj) << checkXRange(obj) << std::endl;
//    std::cout << "Ground::checkTop obj->dy: " << obj->dy << " proslijedjeni dy: " << dy << std::endl;

//    std::cout << getStringTypeOfObject(this) << " " << this->y << " " << getStringTypeOfObject(obj) << obj->testingY << std::endl;
    if(checkYTop(obj) && checkXRange(obj) && (obj->dy >= 0))
    {
//        std::cout << obj->getStringTypeOfObject() << " hit top of ground " << obj->dy << std::endl;
        if(obj->typeOfObject == objectType::Mario)
        {
            obj->setYState(stateY::Neutral);
        }
//        obj->dy = obj->testingY - obj->y;
        obj->ground = obj->testingY + obj->bottomSide;
        return true;
    }
    return false;
}

bool Ground::checkLeft(std::shared_ptr<Object> obj, int dx)
{
    if(falseGround)
    {
        return false;
    }

    if(obj->typeOfObject == this->objectType::Fireball)
    {
        return false;
    }

    if(checkYRange(obj) && checkXLeft(obj) && (obj->dx > 0))
    {
//        std::cout << "----------------------------------\n";
//        std::cout << obj->getStringTypeOfObject() << " hit left side of ground\n";
//        std::cout << "----------------------------------\n";
        return true;
    }
    return false;
}

bool Ground::checkRight(std::shared_ptr<Object> obj, int dx)
{
    if(falseGround)
    {
        return false;
    }

    if(obj->typeOfObject == this->objectType::Fireball)
    {
        return false;
    }

    if(checkYRange(obj) && checkXRight(obj) && (obj->dx < 0))
    {
//        std::cout << "----------------------------------\n";
        std::cout << obj->getStringTypeOfObject() << " hit right side of ground\n";
//        std::cout << "----------------------------------\n";
        return true;
    }
    return false;
}

void Ground::moveYX()
{
    // ground se ne krece
}

void Ground::moveY()
{

}
void Ground::moveX()
{

}

const std::string Ground::getStringTypeOfObject() const
{
    return std::string("Ground");
}

