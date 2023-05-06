#include "Object.hpp"
#include "Image.hpp"

class Turtle : public Object
{
private:

public:
    WrapperRAII::Image left_ = WrapperRAII::Image("\\resources\\turtleLeft.bmp");
    WrapperRAII::Image leftMask_ = WrapperRAII::Image("\\resources\\turtleLeftBlack.bmp");
    WrapperRAII::Image right_ = WrapperRAII::Image("\\resources\\turtleRight.bmp");
    WrapperRAII::Image rightMask_ = WrapperRAII::Image("\\resources\\turtleRightBlack.bmp");

    HBITMAP hbmLeft_ = left_.getHBitmap();
    HBITMAP hbmLeftMask_ = leftMask_.getHBitmap();
    HBITMAP hbmRight_ = right_.getHBitmap();
    HBITMAP hbmRightMask_ = rightMask_.getHBitmap();

    Turtle(int x, int y);

    bool checkBottom(std::shared_ptr<Object> obj, int dy_) override;
    bool checkTop(std::shared_ptr<Object> obj, int dy_) override;
    bool checkLeft(std::shared_ptr<Object> obj, int dx_) override;
    bool checkRight(std::shared_ptr<Object> obj, int dx_) override;
    const std::string getStringTypeOfObject(void) const override;
    void decreaseLife() override;
    void increaseLife() override;
    void draw(HDC hdcBuffer, HDC hdcMem) override;
    void afterDraw() override;
    void stompY(std::shared_ptr<Object> obj) override;
    void collideX(std::shared_ptr<Object> obj) override;
};
