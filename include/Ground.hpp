#pragma once
#include "Mario.hpp"

class Ground : public Object
{
private:
    WrapperRAII::Image ground_ = WrapperRAII::Image("\\resources\\ground.bmp");
    WrapperRAII::Image groundMask_ = WrapperRAII::Image("\\resources\\groundBlack.bmp");

    HBITMAP hbmGround_ = ground_.getHBitmap();
    HBITMAP hbmGroundMask_ = groundMask_.getHBitmap();
public:
    Ground(int x, int y, int falseGround = false);
    bool checkBottom(std::shared_ptr<Object> obj, int dy_) override;
    bool checkTop(std::shared_ptr<Object> obj, int dy_)override;
    bool checkLeft(std::shared_ptr<Object> obj, int dx_)override;
    bool checkRight(std::shared_ptr<Object> obj, int dx_)override;

    void moveYX()override;
    void moveY()override;
    void moveX()override;
    const std::string getStringTypeOfObject() const override;
    bool falseGround = false;
};
