#pragma once
#include "Mario.hpp"

class Ground : public Object
{
private:
//    BITMAP bitmap;
    HBITMAP ground = (HBITMAP) LoadImage(NULL, "ground.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP groundMask = (HBITMAP) LoadImage(NULL, "groundBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
public:
    Ground(int x, int y);
    bool checkBottom(std::shared_ptr<Object> obj, int dy) override;
    bool checkTop(std::shared_ptr<Object> obj, int dy)override;
    bool checkLeft(std::shared_ptr<Object> obj)override;
    bool checkRight(std::shared_ptr<Object> obj)override;

    void moveYX(std::shared_ptr<Object> obj, bool whosMoving)override;
    void moveY(std::shared_ptr<Object> obj, bool whosMoving)override;
    void moveX(std::shared_ptr<Object> obj, bool whosMoving)override;
};
