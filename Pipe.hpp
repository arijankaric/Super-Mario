#pragma once
#include "Mario.hpp"

class Pipe : public Object
{
private:

public:
    Pipe(int x, int y, vektorObjekata obj, vektorObjekata movObj);
    bool checkBottom(std::shared_ptr<Object> obj, int dy) override;
    bool checkTop(std::shared_ptr<Object> obj, int dy)override;
    bool checkLeft(std::shared_ptr<Object> obj)override;
    bool checkRight(std::shared_ptr<Object> obj)override;

    void moveYX(std::shared_ptr<Object> obj, bool whosMoving)override;
    void moveY(std::shared_ptr<Object> obj, bool whosMoving)override;
    void moveX(std::shared_ptr<Object> obj, bool whosMoving)override;
};
