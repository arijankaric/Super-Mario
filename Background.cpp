#include "Background.hpp"

Background::Background()
{
    this->hbm_ = (HBITMAP) LoadImage(NULL, "background.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    this->hbmMask_ = (HBITMAP) LoadImage(NULL, "backgroundBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    GetObject(hbm_, sizeof(BITMAP), &bitmap);
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
//bool Background::checkTop(std::shared_ptr<Object> obj, int dy)
//{
//    std::cout << "why is this being called\n";
//    return true;
//}
//
//bool Background::checkBottom(std::shared_ptr<Object> obj, int dy)
//{
//    std::cout << "why is this being called\n";
//    return true;
//}
