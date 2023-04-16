#pragma once

#include "distanceBetweenObjects.hpp"

class Background : public Object
{
private:
//    HBITMAP hbmBackground = (HBITMAP) LoadImage(NULL, "background.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//    HBITMAP hbmBackgroundMask = (HBITMAP) LoadImage(NULL, "backgroundBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
public:
    Background();
//    bool checkBottom(std::shared_ptr<Object> obj, int dy_) override;
//    bool checkTop(std::shared_ptr<Object> obj, int dy_)override;
//    bool checkLeft(std::shared_ptr<Object> obj, int dx_)override;
//    bool checkRight(std::shared_ptr<Object> obj, int dx_)override;
    const std::string getStringTypeOfObject() const override;
};
