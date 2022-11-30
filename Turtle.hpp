#include "Object.hpp"

class Turtle : public Object
{
private:

public:
    HBITMAP left = (HBITMAP) LoadImage(NULL, "turtleLeft.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP leftMask = (HBITMAP) LoadImage(NULL, "turtleLeftBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP right = (HBITMAP) LoadImage(NULL, "turtleRight.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP rightMask = (HBITMAP) LoadImage(NULL, "turtleRightBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    Turtle(int x, int y);

    bool checkBottom(std::shared_ptr<Object> obj, int dy) override;
    bool checkTop(std::shared_ptr<Object> obj, int dy) override;
    bool checkLeft(std::shared_ptr<Object> obj, int dx) override;
    bool checkRight(std::shared_ptr<Object> obj, int dx) override;
    const std::string getStringTypeOfObject(void) const override;
    void decreaseLife() override;
    void increaseLife() override;
    void draw(HDC hdcBuffer, HDC hdcMem) override;
    void afterDraw() override;
    void stompY(std::shared_ptr<Object> obj) override;
    void collideX(std::shared_ptr<Object> obj) override;
};
