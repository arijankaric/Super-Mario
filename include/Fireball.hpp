#include "Object.hpp"

class Fireball : public Object
{
private:

public:
    Fireball(int x, int y, int dx, int dy);

    bool checkBottom(std::shared_ptr<Object> obj, int dy) override;
    bool checkTop(std::shared_ptr<Object> obj, int dy) override;
    bool checkLeft(std::shared_ptr<Object> obj, int dx) override;
    bool checkRight(std::shared_ptr<Object> obj, int dx) override;
    const std::string getStringTypeOfObject() const override;
};
