#include "Background.hpp"

class Coin : public Object
{
private:
    HBITMAP coin = (HBITMAP) LoadImage(NULL, "Coin.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP coinMask = (HBITMAP) LoadImage(NULL, "CoinBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
public:
    Coin(int x, int y, bool dying = false);
    bool checkBottom(std::shared_ptr<Object> obj) override;
    bool checkTop(std::shared_ptr<Object> obj)override;
    bool checkLeft(std::shared_ptr<Object> obj)override;
    bool checkRight(std::shared_ptr<Object> obj)override;
};
