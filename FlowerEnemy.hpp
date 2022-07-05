#pragma once

#include "Mario.hpp"

class FlowerEnemy : public Object
{
private:
//    BITMAP bitmap;
    HBITMAP enemy = (HBITMAP) LoadImage(NULL, "enemy.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP enemyMask = (HBITMAP) LoadImage(NULL, "enemyBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
public:
    FlowerEnemy(int x, int y);
    bool checkBottom(std::shared_ptr<Object> obj) override;
    bool checkTop(std::shared_ptr<Object> obj)override;
    bool checkLeft(std::shared_ptr<Object> obj)override;
    bool checkRight(std::shared_ptr<Object> obj)override;
};
