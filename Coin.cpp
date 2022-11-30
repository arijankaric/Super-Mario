#include "Coin.hpp"

Coin::Coin(int x, int y, bool dying)
{
//    this->objects = obj;
//    this->movingObjects = movObj;
    this->x = x;
    this->y = y;
    this->dy = -15;
    this->hbm_ = coin;
    this->hbmMask_ = coinMask;
    GetObject(this->hbm_, sizeof(BITMAP), &bitmap);
    this->width = bitmap.bmWidth/5;
    this->height = bitmap.bmHeight;
    this->max = 5;
    this->X = 0;
    if(dying)
        this->cyclesUntilDeath = 10;
    this->typeOfObject = objectType::Coin;
}


bool Coin::checkLeft(std::shared_ptr<Object> obj, int dx)
{
    return false;
}

bool Coin::checkRight(std::shared_ptr<Object> obj, int dx)
{
    return false;
}

bool Coin::checkTop(std::shared_ptr<Object> obj, int dy)
{
    return false;
}

bool Coin::checkBottom(std::shared_ptr<Object> obj, int dy)
{
    return false;
}

void Coin::moveYX()
{
    this->moveY();
    this->moveX();
}
void Coin::moveY()
{
    this->y += this->dy;
}
void Coin::moveX()
{
    this->x += this->dx;
}

const std::string Coin::getStringTypeOfObject() const
{
    return std::string("Coin");
}

void Coin::afterDraw()
{
    if(this->cycles == (this->cyclesUntilDeath/2))
    {
        this->dy = -this->dy;
    }

    if(this->cyclesUntilDeath != -1)
    {
        ++this->cycles;
        std::cout << "Only dying coin should print this: " << this->cycles << std::endl;
    }

    if(this->cyclesUntilDeath == this->cycles)
    {
        this->removeDeadObject(shared_from_this());
//        objects->erase(partition(std::begin(*objects), end(*objects),
//                                 [this](const std::shared_ptr<Object> &x)
//        {
//            return (x.get() != this);
//        }),
//        std::end(*objects));
//            objects->erase(std::remove(objects->begin(), objects->end(), *this), objects->end());
    }
}
