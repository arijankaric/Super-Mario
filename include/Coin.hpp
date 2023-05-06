#include "Background.hpp"
#include "./Image.hpp"

class Coin : public Object
{
private:
    WrapperRAII::Image Coin_ = WrapperRAII::Image("\\resources\\Coin.bmp");
    WrapperRAII::Image CoinMask_ = WrapperRAII::Image("\\resources\\CoinBlack.bmp");

    HBITMAP hbmCoin_ = Coin_.getHBitmap();
    HBITMAP hbmCoinMask_ = CoinMask_.getHBitmap();
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
