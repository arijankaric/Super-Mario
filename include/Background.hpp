#pragma once

#include "distanceBetweenObjects.hpp"
#include "./Image.hpp"

class Background : public Object
{
private:
    WrapperRAII::Image background_ = WrapperRAII::Image("\\resources\\background.bmp");
    WrapperRAII::Image backgroundMask_ = WrapperRAII::Image("\\resources\\backgroundBlack.bmp");

    HBITMAP hbmBackground_ = background_.getHBitmap();
    HBITMAP hbmBackgroundMask_ = backgroundMask_.getHBitmap();
public:
    Background();
//    bool checkBottom(std::shared_ptr<Object> obj, int dy_) override;
//    bool checkTop(std::shared_ptr<Object> obj, int dy_)override;
//    bool checkLeft(std::shared_ptr<Object> obj, int dx_)override;
//    bool checkRight(std::shared_ptr<Object> obj, int dx_)override;
    const std::string getStringTypeOfObject() const override;
};
