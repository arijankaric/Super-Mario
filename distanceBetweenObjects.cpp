#include "distanceBetweenObjects.hpp"

int distanceBetweenObjects(const std::shared_ptr<Object> obj1, const std::shared_ptr<Object> obj2)
{
    return sqrt(pow((obj1->x - obj2->x),2) + pow((obj1->y - obj2->y),2));
}
