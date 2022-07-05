#include "DrawObjekat.hpp"

#include <windows.h>

void DrawObjekat(HDC hdc, RECT* rect)
{
//    std::cout << "-----------------------------------------------------------\n";
//    std::cout << "Drawing\n";
//    std::cout << "-----------------------------------------------------------\n";
    HDC hdcBuffer = CreateCompatibleDC(hdc);
    HBITMAP hbmBuffer = CreateCompatibleBitmap(hdc, rect->right, rect->bottom);
    HBITMAP hbmOldBuffer = (HBITMAP) SelectObject(hdcBuffer, hbmBuffer);

    HDC hdcMem = CreateCompatibleDC(hdc);
    HBITMAP hbmOld1 = (HBITMAP) SelectObject(hdcMem, background->hbm_);
    BitBlt(hdcBuffer, 0, 0, background->width, background->height, hdcMem, background->x, background->y, SRCCOPY);

//    SelectObject(hdc, hbmOld1);

    for(std::shared_ptr<Object>& el : objects)
    {
        if(el->hbm_ == NULL || el->hbmMask_ == NULL)
            continue;



        if(el->typeOfObject == FLOWER_ENEMY)
        {
            int height = el->startingY - el->y;
            SelectObject(hdcMem, el->hbm_);
            BitBlt(hdcBuffer, el->x, el->y, el->width, height, hdcMem, el->X*el->width, 0, SRCAND);

            SelectObject(hdcMem, el->hbmMask_);
            BitBlt(hdcBuffer, el->x, el->y, el->width, height, hdcMem, el->X*el->width, 0, SRCPAINT);
        }
        else
        {
            SelectObject(hdcMem, el->hbm_);
            BitBlt(hdcBuffer, el->x, el->y, el->width, el->height, hdcMem, el->X*el->width, 0, SRCAND);

            SelectObject(hdcMem, el->hbmMask_);
            BitBlt(hdcBuffer, el->x, el->y, el->width, el->height, hdcMem, el->X*el->width, 0, SRCPAINT);
        }

        if(++el->changeCycles == el->cyclesForChange)
        {
            ++el->X;
            el->changeCycles = 0;
        }

        if(el->X == el->max)
        {
            el->X = 0;
        }
    }


//    SelectObject(hdcMem, hbmForeground);
//    BitBlt(hdcBuffer, 0, 0, foreground.width, foreground.height, hdcMem, foreground.x, foreground.y, SRCAND);
//
//
//    SelectObject(hdcMem, hbmForegroundMask);
//    BitBlt(hdcBuffer, 0, 0, foreground.width, foreground.height, hdcMem, foreground.x, foreground.y, SRCPAINT);

//    SelectObject(hdcMem, hbmMarioWalk);
//    BitBlt(hdcBuffer, mario.x, mario.y, mario.width, mario.height, hdcMem, mario.objectX*mario.width, mario.objectY*mario.height, SRCAND);
//
//
//    SelectObject(hdcMem, hbmMarioWalkMask);
//    BitBlt(hdcBuffer, mario.x, mario.y, mario.width, mario.height, hdcMem, mario.objectX*mario.width, mario.objectY*mario.height, SRCPAINT);

    //const POINT lpPoint[] = {{250, 250}, {335, 164}, {391, 391}, {476, 306}};
    //const POINT lpPoint[] = {{500,500}, {670.61, 329.39},{641.84, 641.84}, {783.68, 783.68}};

    BitBlt(hdc, 0,0, rect->right, rect->bottom, hdcBuffer, 0,0, SRCCOPY);

    DeleteObject(hdcMem);
    DeleteObject(hbmBuffer);

    SelectObject(hdcBuffer, hbmOldBuffer);
    DeleteObject(hdcBuffer);
    DeleteObject(hbmOldBuffer);

    for(const std::shared_ptr<Object>& el : objects)
    {
        if(el->outline)
        {
            int x1 = el->x + el->leftSide;
            int x2 = x1;
            int y1 = el->y + el->topSide;
            int y2 = el->y + el->bottomSide;
            MoveToEx(hdc, x1, y1, NULL);
            LineTo(hdc, x2, y2);
            x1 = el->x + el->leftSide;
            x2 = el->x + el->rightSide;
            y1 = el->y + el->topSide;
            y2 = y1;
//            std::cout << "topSide: " << y1 << std::endl;
            MoveToEx(hdc, x1, y1, NULL);
            LineTo(hdc, x2, y2);
            x1 = el->x + el->rightSide;
            x2 = x1;
            y1 = el->y + el->topSide;
            y2 = el->y + el->bottomSide;
            MoveToEx(hdc, x1, y1, NULL);
            LineTo(hdc, x2, y2);
            x1 = el->x + el->leftSide;
            x2 = el->x + el->rightSide;
            y1 = el->y + el->bottomSide;
            y2 = y1;
//            std::cout << "bottomSide: " << y1 << std::endl;
            MoveToEx(hdc, x1, y1, NULL);
            LineTo(hdc, x2, y2);
        }
    }
//    if(mario->outline)
//    {
//        int x1 = mario->x + mario->leftSide;
//        int x2 = x1;
//        int y1 = mario->y + mario->topSide;
//        int y2 = mario->y + mario->bottomSide;
//        MoveToEx(hdc, x1, y1, NULL);
//        LineTo(hdc, x2, y2);
//        x1 = mario->x + mario->leftSide;
//        x2 = mario->x + mario->rightSide;
//        y1 = mario->y + mario->topSide;
//        y2 = y1;
////        std::cout << "topSide: " << y1 << std::endl;
//        MoveToEx(hdc, x1, y1, NULL);
//        LineTo(hdc, x2, y2);
//        x1 = mario->x + mario->rightSide;
//        x2 = x1;
//        y1 = mario->y + mario->topSide;
//        y2 = mario->y + mario->bottomSide;
//        MoveToEx(hdc, x1, y1, NULL);
//        LineTo(hdc, x2, y2);
//        x1 = mario->x + mario->leftSide;
//        x2 = mario->x + mario->rightSide;
//        y1 = mario->y + mario->bottomSide;
//        y2 = y1;
////        std::cout << "bottomSide: " << y1 << std::endl;
//        MoveToEx(hdc, x1, y1, NULL);
//        LineTo(hdc, x2, y2);
//    }
}
