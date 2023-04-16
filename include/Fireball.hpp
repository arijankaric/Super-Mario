#include "Object.hpp"

class Fireball : public Object
{
private:

public:
    Fireball(int x, int y, int dx_, int dy_);

    bool checkBottom(std::shared_ptr<Object> obj, int dy_) override;
    bool checkTop(std::shared_ptr<Object> obj, int dy_) override;
    bool checkLeft(std::shared_ptr<Object> obj, int dx_) override;
    bool checkRight(std::shared_ptr<Object> obj, int dx_) override;
    const std::string getStringTypeOfObject() const override;
};
