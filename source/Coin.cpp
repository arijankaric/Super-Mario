#include "../include/Coin.hpp"

Coin::Coin(int x, int y, bool dy_ing)
{
//    this->objects = obj;
//    this->movingObjects = movObj;
    this->x = x;
    this->y = y;
    this->dy_ = -15;
    this->hbm_ = hbmCoin_;
    this->hbmMask_ = hbmCoinMask_;
    GetObject(this->hbm_, sizeof(BITMAP), &bitmap);
    this->width = bitmap.bmWidth/5;
    this->height = bitmap.bmHeight;
    this->maxCycles_ = 5;
    this->X_ = 0;
    if(dy_ing)
        this->cyclesUntilDeath = 10;
    this->typeOfObject = objectType::Coin;
}


bool Coin::checkLeft(std::shared_ptr<Object> obj, int dx_)
{
    return false;
}

bool Coin::checkRight(std::shared_ptr<Object> obj, int dx_)
{
    return false;
}

bool Coin::checkTop(std::shared_ptr<Object> obj, int dy_)
{
    return false;
}

bool Coin::checkBottom(std::shared_ptr<Object> obj, int dy_)
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
    this->y += this->dy_;
}
void Coin::moveX()
{
    this->x += this->dx_;
}

const std::string Coin::getStringTypeOfObject() const
{
    return std::string("Coin");
}

void Coin::afterDraw()
{
    if(this->cycles == (this->cyclesUntilDeath/2))
    {
        this->dy_ = -this->dy_;
    }

    if(this->cyclesUntilDeath != -1)
    {
        ++this->cycles;
        std::cout << "Only dy_ing coin should print this: " << this->cycles << std::endl;
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
