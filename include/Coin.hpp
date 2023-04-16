#include "Background.hpp"

class Coin : public Object
{
private:
    HBITMAP coin = (HBITMAP) LoadImage(NULL, "Coin.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP coinMask = (HBITMAP) LoadImage(NULL, "CoinBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
public:
    Coin(int x, int y, bool dy_ing = false);
    bool checkBottom(std::shared_ptr<Object> obj, int dy_) override;
    bool checkTop(std::shared_ptr<Object> obj, int dy_)override;
    bool checkLeft(std::shared_ptr<Object> obj, int dx_)override;
    bool checkRight(std::shared_ptr<Object> obj, int dx_)override;

    void moveYX()override;
    void moveY()override;
    void moveX()override;
    const std::string getStringTypeOfObject() const override;
    void afterDraw() override;
};
