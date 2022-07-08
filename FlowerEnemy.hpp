#pragma once

#include "Mario.hpp"

class FlowerEnemy : public Object
{
private:
//    BITMAP bitmap;
    HBITMAP enemy = (HBITMAP) LoadImage(NULL, "enemy.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP enemyMask = (HBITMAP) LoadImage(NULL, "enemyBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
public:
    FlowerEnemy(vektorObjekata obj, vektorObjekata movObj, int x, int y, TIMERPROC upFunc, TIMERPROC downFunc);
    bool checkBottom(std::shared_ptr<Object> obj, int dy) override;
    bool checkTop(std::shared_ptr<Object> obj, int dy)override;
    bool checkLeft(std::shared_ptr<Object> obj, int dx)override;
    bool checkRight(std::shared_ptr<Object> obj, int dx)override;
    void draw(HDC hdcBuffer, HDC hdcMem)override;

    void moveYX(std::shared_ptr<Object> obj, bool whosMoving)override;
    void moveY(std::shared_ptr<Object> obj, bool whosMoving)override;
    void moveX(std::shared_ptr<Object> obj, bool whosMoving)override;

    TIMERPROC upFunc_;
    TIMERPROC downFunc_;
};
