#pragma once

#include "Mario.hpp"
#include "Fireball.hpp"
#include "Pipe.hpp"

class FlowerEnemy : public Object
{
private:
//    BITMAP bitmap;
    HBITMAP left = (HBITMAP) LoadImage(NULL, "flowerEnemyLeft.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP leftMask = (HBITMAP) LoadImage(NULL, "flowerEnemyLeftBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP right = (HBITMAP) LoadImage(NULL, "flowerEnemyRight.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP rightMask = (HBITMAP) LoadImage(NULL, "flowerEnemyRightBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
public:
    enum class flowerType{eater, thrower};
    FlowerEnemy(int x, int y, TIMERPROC upFunc, TIMERPROC downFunc);
    FlowerEnemy(int x, int y, std::shared_ptr<Object> parentPipe, flowerType choice = flowerType::eater);
    std::shared_ptr<Object> parentPipe_;

    // eater - opens/closes mouth cyclically
    // thrower - throws slow traveling fireballs in quadrant that Mario resides in
    flowerType typeOfFlowerEnemy;

    bool checkBottom(std::shared_ptr<Object> obj, int dy_) override;
    bool checkTop(std::shared_ptr<Object> obj, int dy_)override;
    bool checkLeft(std::shared_ptr<Object> obj, int dx_)override;
    bool checkRight(std::shared_ptr<Object> obj, int dx_)override;
    void draw(HDC hdcBuffer, HDC hdcMem)override;

    void moveYX()override;
    void moveY()override;
    void moveX()override;

    TIMERPROC upFunc_;
    TIMERPROC downFunc_;

    const std::string getStringTypeOfObject() const override;

    void getDirection(int quadrant);
    void afterDraw() override;
    std::pair<int, int> direction_;
};
