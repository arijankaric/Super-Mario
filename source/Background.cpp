#include "../include/Background.hpp"

Background::Background()
{
    this->hbm_ = hbmBackground_;
    this->hbmMask_ = hbmBackground_;
    GetObject(this->hbm_, sizeof(BITMAP), &bitmap);
    this->width = bitmap.bmWidth;
    this->height = bitmap.bmHeight;
    this->x = 0;
    this->y = this->height - VISINAPROZORA - 155;
}

//bool Background::checkLeft(std::shared_ptr<Object> obj)
//{
//    return true;
//}
//
//bool Background::checkRight(std::shared_ptr<Object> obj)
//{
//    return true;
//}
//
//bool Background::checkTop(std::shared_ptr<Object> obj, int dy_)
//{
//    std::cout << "why is this being called\n";
//    return true;
//}
//
//bool Background::checkBottom(std::shared_ptr<Object> obj, int dy_)
//{
//    std::cout << "why is this being called\n";
//    return true;
//}

const std::string Background::getStringTypeOfObject() const
{
    return std::string("Background");
}
