#include "distanceBetweenObjects.hpp"

int distanceBetweenObjects(const Object* obj1, const Object* obj2) noexcept
{
    return sqrt(pow((obj1->centerX() - obj2->centerX()),2) + pow((obj1->centerY() - obj2->centerY()),2));
}
