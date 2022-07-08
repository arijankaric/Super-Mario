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

bool Ground::checkBottom(std::shared_ptr<Object> obj, int dy)
{
//    std::cout << "Ground::checkBottom obj->dy: " << obj->dy << " proslijedjeni dy: " << dy << std::endl;
    if(checkYBottom(obj) && checkXRange(obj) && (dy < 0))
    {
//        std::cout << getStringTypeOfObject(obj) << " hit bottom of ground" << std::endl;
        obj->setYState(stateY::Down);
        --(obj->testingY);
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
//    std::cout << obj->y + obj->bottomSide << " " << this->y + this->topSide << " " << checkYTop(obj) << checkXRange(obj) << std::endl;
//    std::cout << "Ground::checkTop obj->dy: " << obj->dy << " proslijedjeni dy: " << dy << std::endl;

//    std::cout << getStringTypeOfObject(this) << " " << this->y << " " << getStringTypeOfObject(obj) << obj->testingY << std::endl;
    if(checkYTop(obj) && checkXRange(obj) && (obj->dy >= 0))
    {
//        std::cout << getStringTypeOfObject(obj) << " hit top of ground " << obj->dy << std::endl;
        obj->setYState(stateY::Neutral);
//        obj->dy = obj->testingY - obj->y;
        obj->ground = obj->testingY + obj->bottomSide;
        return true;
    }
    return false;
}

bool Ground::checkLeft(std::shared_ptr<Object> obj, int dx)
{
    if(checkYRange(obj) && checkXLeft(obj) && (obj->dx > 0))
    {
//        std::cout << "----------------------------------\n";
//        std::cout << getStringTypeOfObject(obj) << " hit left side of ground\n";
//        std::cout << "----------------------------------\n";
        return true;
    }
    return false;
}

bool Ground::checkRight(std::shared_ptr<Object> obj, int dx)
{
    if(checkYRange(obj) && checkXRight(obj) && (obj->dx < 0))
    {
//        std::cout << "----------------------------------\n";
//        std::cout << getStringTypeOfObject(obj) << " hit right side of ground\n";
//        std::cout << "----------------------------------\n";
        return true;
    }
    return false;
}

void Ground::moveYX(std::shared_ptr<Object> obj, bool whosMoving)
{
    // ground se ne krece
}

void Ground::moveY(std::shared_ptr<Object> obj, bool whosMoving)
{

}
void Ground::moveX(std::shared_ptr<Object> obj, bool whosMoving)
{

}

