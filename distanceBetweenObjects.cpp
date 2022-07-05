#include "distanceBetweenObjects.hpp"

int distanceBetweenObjects(const Object* obj1, const Object* obj2) noexcept
{
    return sqrt(pow((obj1->x - obj2->x),2) + pow((obj1->y - obj2->y),2));
}
