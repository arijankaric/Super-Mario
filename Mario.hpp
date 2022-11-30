#pragma once

#include "Background.hpp"
#include <windows.h>
#include <iostream>
#include <vector>

class Mario : public Object
{
private:
    HBITMAP hbmMarioWalkLeft = (HBITMAP) LoadImage(NULL, "SmallMarioLeft.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP hbmMarioWalkLeftMask = (HBITMAP) LoadImage(NULL, "SmallMarioLeftBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP hbmMarioWalkRight = (HBITMAP) LoadImage(NULL, "SmallMarioRight.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP hbmMarioWalkRightMask = (HBITMAP) LoadImage(NULL, "SmallMarioRightBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP hbmMarioDead_ = (HBITMAP) LoadImage(NULL, "marioDead.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP hbmMarioDeadMask_ = (HBITMAP) LoadImage(NULL, "marioDeadBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP hbmSuperMarioWalkLeft_ = (HBITMAP) LoadImage(NULL, "superMarioLeft.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP hbmSuperMarioWalkLeftMask_ = (HBITMAP) LoadImage(NULL, "superMarioLeftBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP hbmSuperMarioWalkRight_ = (HBITMAP) LoadImage(NULL, "superMarioRight.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP hbmSuperMarioWalkRightMask_ = (HBITMAP) LoadImage(NULL, "superMarioRightBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
public:
    Mario(int x = 0, int y = 0);
    enum class marioState{small, super, raccoon, sparkling};
    marioState st_ = marioState::small;
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
    void nextDY(void) override;
//    void changeY(int dy);

    const std::string getStringTypeOfObject() const override;

    void collideX(std::shared_ptr<Object> obj) override;

    void animateMarioDeath();
    const bool deadly(const std::shared_ptr<Object> obj) const override;
//    void moveYX() override;
    void projectY() override;
};
