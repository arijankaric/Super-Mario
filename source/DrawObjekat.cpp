#include "../include/Game.hpp"

void Game::DrawObjekat(HDC hdc)
{
//    std::cout << "-----------------------------------------------------------\n";
//    std::cout << "Drawing\n";
//    std::cout << "-----------------------------------------------------------\n";

    HDC hdcBuffer = CreateCompatibleDC(hdc);
    HBITMAP hbmBuffer = CreateCompatibleBitmap(hdc, clientRect->right, clientRect->bottom);
    HBITMAP hbmOldBuffer = (HBITMAP) SelectObject(hdcBuffer, hbmBuffer);

    HDC hdcMem = CreateCompatibleDC(hdc);
    HBITMAP hbmOld1 = (HBITMAP) SelectObject(hdcMem, background->hbm_);
    DeleteObject(hbmOld1);
    BitBlt(hdcBuffer, 0, 0, background->width, background->height, hdcMem, background->x, background->y, SRCCOPY);

    // SelectObject(hdc, hbmOld1);

    for(std::shared_ptr<Object>& el : *objects)
    {
        if(el->isSprite() && ((el->hbm_ == nullptr) || (el->hbmMask_ == nullptr)))
        {
            std::cout << "Printing object that doesn't have a hbm_ or a hbmMask_ but should have" << std::endl;
            std::cout << el->getStringTypeOfObject() << std::endl;
            continue;
        }


        el->draw(hdcBuffer, hdcMem);
        el->afterDraw();
    }

    for(std::shared_ptr<Object>& el : *movingObjects)
    {
        std::cout << "Moving objects exist!\n";
        if(el->hbm_ == NULL || el->hbmMask_ == NULL)
            continue;

        el->draw(hdcBuffer, hdcMem);

        if(mario->stX_ != Object::stateX::Neutral)
        {
            mario->maxCycles_ = 2;
        }
        else
        {
            mario->maxCycles_ = 1;
        }

        if(mario->Y_ != 3)
        {
            if(++el->changeCycles == el->cyclesForChange)
            {
                ++el->X_;
                el->changeCycles = 0;
            }
            if(mario->X_ == 2)
                mario->X_ = 0;
        }

        if(el->X_ >= el->maxCycles_)
        {
            el->X_ = 0;
        }
    }

    BitBlt(hdc, 0,0, clientRect->right, clientRect->bottom, hdcBuffer, 0,0, SRCCOPY);

    DeleteObject(hdcMem);
    DeleteObject(hbmBuffer);

    SelectObject(hdcBuffer, hbmOldBuffer);
    DeleteObject(hdcBuffer);
    DeleteObject(hbmOldBuffer);

    for(const std::shared_ptr<Object>& el : *objects)
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

    for(const std::shared_ptr<Object>& el : *movingObjects)
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
}
