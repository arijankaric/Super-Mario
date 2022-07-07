#pragma once
#include "Mario.hpp"

class QuestionBlock : public Object
{
private:
    HBITMAP questionMark = (HBITMAP) LoadImage(NULL, "QuestionMarkBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP questionMarkMask = (HBITMAP) LoadImage(NULL, "QuestionMark.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP emptyQuestionMark = (HBITMAP) LoadImage(NULL, "emptyQuestionBlockBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP emptyQuestionMarkMask = (HBITMAP) LoadImage(NULL, "emptyQuestionBlock.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

public:
    QuestionBlock(vektorObjekata obj, vektorObjekata movObj, int x, int y);
    bool checkBottom(std::shared_ptr<Object> obj, int dy) override;
    bool checkTop(std::shared_ptr<Object> obj, int dy)override;
    bool checkLeft(std::shared_ptr<Object> obj)override;
    bool checkRight(std::shared_ptr<Object> obj)override;

    void moveYX(std::shared_ptr<Object> obj, bool whosMoving)override;
    void moveY(std::shared_ptr<Object> obj, bool whosMoving)override;
    void moveX(std::shared_ptr<Object> obj, bool whosMoving)override;
};
