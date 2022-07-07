#include "Coin.hpp"

Coin::Coin(vektorObjekata obj, vektorObjekata movObj, int x, int y, bool dying)
{
    this->objects = obj;
    this->movingObjects = movObj;
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
    if(outline)
        this->outline = true;
    this->typeOfObject = COIN;
}

bool Coin::checkLeft(std::shared_ptr<Object> obj)
{

}

bool Coin::checkRight(std::shared_ptr<Object> obj)
{

}

bool Coin::checkTop(std::shared_ptr<Object> obj)
{

}

bool Coin::checkBottom(std::shared_ptr<Object> obj)
{

}
