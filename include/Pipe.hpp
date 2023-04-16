#pragma once
#include "Mario.hpp"

class Pipe : public Object
{
private:

public:
    Pipe(int x, int y);
    bool checkBottom(std::shared_ptr<Object> obj, int dy_) override;
    bool checkTop(std::shared_ptr<Object> obj, int dy_)override;
    bool checkLeft(std::shared_ptr<Object> obj, int dx_)override;
    bool checkRight(std::shared_ptr<Object> obj, int dx_)override;

    void moveYX()override;
    void moveY()override;
    void moveX()override;
    const std::string getStringTypeOfObject() const override;
    void collideX(std::shared_ptr<Object> obj) override;
};
