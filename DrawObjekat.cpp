#include "Game.hpp"

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
    BitBlt(hdcBuffer, 0, 0, background->width, background->height, hdcMem, background->x, background->y, SRCCOPY);

//    SelectObject(hdc, hbmOld1);

    for(std::shared_ptr<Object>& el : *objects)
    {

        if((el->hbm_ == nullptr) || (el->hbmMask_ == nullptr))
            continue;

        el->draw(hdcBuffer, hdcMem);

        if(++el->changeCycles == el->cyclesForChange)
        {
            ++el->X;
            el->changeCycles = 0;
        }

        if(el->X >= el->max)
        {
            el->X = 0;
        }
    }

    for(std::shared_ptr<Object>& el : *movingObjects)
    {
        if(el->hbm_ == NULL || el->hbmMask_ == NULL)
            continue;

        el->draw(hdcBuffer, hdcMem);

        if(mario->stX_ != Object::stateX::Neutral)
        {
            mario->max = 2;
        }
        else
        {
            mario->max = 1;
        }

        if(mario->Y != 3)
        {
            if(++el->changeCycles == el->cyclesForChange)
            {
                ++el->X;
                el->changeCycles = 0;
            }
            if(mario->X == 2)
                mario->X = 0;
        }

        if(el->X >= el->max)
        {
            el->X = 0;
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
