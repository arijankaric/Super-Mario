#pragma once

#include "Background.hpp"
#include "./Image.hpp"
#include <windows.h>
#include <iostream>
#include <vector>

class Mario : public Object
{
private:
    WrapperRAII::Image MarioDeadMask_ = WrapperRAII::Image("\\resources\\marioDeadBlack.bmp");
    WrapperRAII::Image MarioWalkLeft_ = WrapperRAII::Image("\\resources\\SmallMarioLeft.bmp");
    WrapperRAII::Image MarioWalkLeftMask_ = WrapperRAII::Image("\\resources\\SmallMarioLeftBlack.bmp");
    WrapperRAII::Image MarioWalkRight_ = WrapperRAII::Image("\\resources\\SmallMarioRight.bmp");
    WrapperRAII::Image MarioWalkRightMask_ = WrapperRAII::Image("\\resources\\SmallMarioRightBlack.bmp");
    WrapperRAII::Image MarioDead_ = WrapperRAII::Image("\\resources\\marioDead.bmp");
    WrapperRAII::Image SuperMarioWalkLeft_ = WrapperRAII::Image("\\resources\\superMarioLeft.bmp");
    WrapperRAII::Image SuperMarioWalkLeftMask_ = WrapperRAII::Image("\\resources\\superMarioLeftBlack.bmp");
    WrapperRAII::Image SuperMarioWalkRight_ = WrapperRAII::Image("\\resources\\superMarioRight.bmp");
    WrapperRAII::Image SuperMarioWalkRightMask_ = WrapperRAII::Image("\\resources\\superMarioRightBlack.bmp");

    HBITMAP hbmMarioWalkLeft_ = MarioWalkLeft_.getHBitmap();
    HBITMAP hbmMarioWalkLeftMask_ = MarioWalkLeftMask_.getHBitmap();
    HBITMAP hbmMarioWalkRight_ = MarioWalkRight_.getHBitmap();
    HBITMAP hbmMarioWalkRightMask_ = MarioWalkRightMask_.getHBitmap();
    HBITMAP hbmMarioDead_ = MarioDead_.getHBitmap();
    HBITMAP hbmMarioDeadMask_ = (HBITMAP) MarioDeadMask_.getHBitmap();
    HBITMAP hbmSuperMarioWalkLeft_ = SuperMarioWalkLeft_.getHBitmap();
    HBITMAP hbmSuperMarioWalkLeftMask_ = SuperMarioWalkLeftMask_.getHBitmap();
    HBITMAP hbmSuperMarioWalkRight_ = SuperMarioWalkRight_.getHBitmap();
    HBITMAP hbmSuperMarioWalkRightMask_ = SuperMarioWalkRightMask_.getHBitmap();
public:
    Mario(int x = 0, int y = 0);
    enum class marioState{regular, super, raccoon, sparkling};
    marioState st_ = marioState::regular;
    void decreaseMarioState(void);
    void setMarioState(marioState st);
//    bool checkBottom(std::shared_ptr<Object> obj) override;
//    bool checkTop(std::shared_ptr<Object> obj)override;
//    bool checkLeft(std::shared_ptr<Object> obj)override;
//    bool checkRight(std::shared_ptr<Object> obj)override;
    void setWalkRight();
    void setWalkLeft();

    void decreaseLife() override;

    void setYState(stateY st) override;
    void setXState(stateX st) override;

//    void nextY(void);
    void nextdy_(void) override;
//    void changeY(int dy_);

    const std::string getStringTypeOfObject() const override;

    void collideX(std::shared_ptr<Object> obj) override;

    void animateMarioDeath();
    const bool deadly(const std::shared_ptr<Object> obj) const override;
//    void moveYX() override;
    void projectY() override;

    HBITMAP getHbmMarioWalkLeft();
    HBITMAP getHbmMarioWalkLeftMask();
    HBITMAP getHbmMarioWalkRight();
    HBITMAP getHbmMarioWalkRightMask();
    HBITMAP getHbmMarioDead();
    HBITMAP getHbmMarioDeadMask();
    HBITMAP getHbmSuperMarioWalkLeft();
    HBITMAP getHbmSuperMarioWalkLeftMask();
    HBITMAP getHbmSuperMarioWalkRight();
    HBITMAP getHbmSuperMarioWalkRightMask();
};
