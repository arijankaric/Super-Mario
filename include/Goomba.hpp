#pragma once

#include "./Object.hpp"
#include "./Image.hpp"

class Goomba : public Object
{
private:
    WrapperRAII::Image goomba_ = WrapperRAII::Image("\\resources\\goomba.bmp");
    WrapperRAII::Image goombaMask_ = WrapperRAII::Image("\\resources\\goombaBlack.bmp");

    HBITMAP hbmGoomba_ = goomba_.getHBitmap();
    HBITMAP hbmGoombaMask_ = goombaMask_.getHBitmap();
public:
    Goomba(int x, int y);
    bool checkBottom(std::shared_ptr<Object> obj, int dy_) override;
    bool checkTop(std::shared_ptr<Object> obj, int dy_)override;
    bool checkLeft(std::shared_ptr<Object> obj, int dx_)override;
    bool checkRight(std::shared_ptr<Object> obj, int dx_)override;
    void moveYX() override;
    const std::string getStringTypeOfObject() const override;
    void decreaseLife() override;
    void afterDraw() override;
};
