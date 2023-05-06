#pragma once
#include "Mario.hpp"

class QuestionBlock : public Object
{
private:
    WrapperRAII::Image questionMark_ = WrapperRAII::Image("\\resources\\QuestionMarkBlack.bmp");
    WrapperRAII::Image questionMarkMask_ = WrapperRAII::Image("\\resources\\QuestionMark.bmp");
    WrapperRAII::Image emptyQuestionMark_ = WrapperRAII::Image("\\resources\\emptyQuestionBlockBlack.bmp");
    WrapperRAII::Image emptyQuestionMarkMask_ = WrapperRAII::Image("\\resources\\emptyQuestionBlock.bmp");

    HBITMAP hbmQuestionMark_ = questionMark_.getHBitmap();
    HBITMAP hbmQuestionMarkMask_ = questionMarkMask_.getHBitmap();
    HBITMAP hbmEmptyQuestionMark_ = emptyQuestionMark_.getHBitmap();
    HBITMAP hbmEmptyQuestionMarkMask_ = emptyQuestionMarkMask_.getHBitmap();

public:
    QuestionBlock(int x, int y);
    bool checkBottom(std::shared_ptr<Object> obj, int dy_) override;
    bool checkTop(std::shared_ptr<Object> obj, int dy_)override;
    bool checkLeft(std::shared_ptr<Object> obj, int dx_)override;
    bool checkRight(std::shared_ptr<Object> obj, int dx_)override;

    void moveYX()override;
    void moveY()override;
    void moveX()override;
    const std::string getStringTypeOfObject() const override;
};
