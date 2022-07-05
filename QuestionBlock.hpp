#pragma once
#include "Mario.hpp"

class QuestionBlock : public Object
{
private:
    HBITMAP questionMark = (HBITMAP) LoadImage(NULL, "QuestionMarkBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP questionMarkMask = (HBITMAP) LoadImage(NULL, "QuestionMark.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

public:
    QuestionBlock(int x, int y);
    bool checkBottom(std::shared_ptr<Object> obj) override;
    bool checkTop(std::shared_ptr<Object> obj)override;
    bool checkLeft(std::shared_ptr<Object> obj)override;
    bool checkRight(std::shared_ptr<Object> obj)override;
};
