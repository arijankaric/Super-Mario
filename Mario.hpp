#pragma once

#include "Background.hpp"
#include <windows.h>
#include <iostream>
#include <vector>

class Mario : public Object
{
public:
    HBITMAP hbmMarioWalkLeft = (HBITMAP) LoadImage(NULL, "SmallMarioLeft.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP hbmMarioWalkLeftMask = (HBITMAP) LoadImage(NULL, "SmallMarioLeftBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP hbmMarioWalkRight = (HBITMAP) LoadImage(NULL, "SmallMarioRight.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP hbmMarioWalkRightMask = (HBITMAP) LoadImage(NULL, "SmallMarioRightBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//    BITMAP bitmap;

    Mario(vektorObjekata obj, vektorObjekata movObj, int x = 0, int y = 0);
//    bool checkBottom(std::shared_ptr<Object> obj) override;
//    bool checkTop(std::shared_ptr<Object> obj)override;
//    bool checkLeft(std::shared_ptr<Object> obj)override;
//    bool checkRight(std::shared_ptr<Object> obj)override;
    void setWalkRight();
    void setWalkLeft();
};

//extern std::shared_ptr<Object> mario;

