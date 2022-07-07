#include "Game.hpp"

Game::Game()
{
    GenerateObjects();
}

void Game::CheckInput(void)
{
//    mario->state = UNKNOWN;
    if(PRITISNUTO(VK_ESCAPE))
    {
        // implementirati pause mehaniku
        exit(0);
    }

    if(PRITISNUTO(VK_UP) && mario->objectY != 3 && mario->objectY != 4)
    {
        mario->stateY = UP;
        mario->objectY = 3;
        mario->objectX = 0;
        mario->dy = -22;
//        if(mario->y <= (VISINAPROZORA/2-mario->height/2 - 10) && ((initial_ground.y - background->y + 211) >= VISINAPROZORA))
//        {
//            std::cout << "camera jumped up\n";
//            ground.y += mario->dy;
//            initial_ground.y += mario->dy;
//            UpdatePositionOfObjects(0, mario->dy);
//        }
//        else if(mario->y + mario->height/2  >= VISINAPROZORA/2 - 10)
//        {
//            std::cout << "mario jumped up\n";
//            mario->y -= mario->dy;
//        }
//        else
//        {
//            std::cout << "SOMETHING WENT WRONG 2\n";
//            // walk in place
//        }
    }
//    else if(mario->y == initial_ground.y)
//    {
//        mario->stateY = NEUTRAL;
//    }

    if(PRITISNUTO(VK_RIGHT))
    {
        mario->stateX = RIGHT;
        if(background->x < (background->width - SIRINAPROZORA) && mario->x == (SIRINAPROZORA/2-mario->width/2))
        {
            uint16_t totalDX = 0;
            uint16_t testDX = 1;
            while(totalDX != mario->dx)
            {
                if(UpdatePositionOfObjects(testDX, 0))
                    mario->startingX += - testDX; // more like mario->startingDX
                else
                    break;
                totalDX += testDX;
            }
//            foreground.x += mario->dx;
        }
        else if(mario->x < (SIRINAPROZORA / 2 - mario->width / 2)) // kad ode skroz na desno
        {
            uint16_t totalDX = 0;
            uint16_t testDX = 1; // smoother walking("more precise")/updating
            while(totalDX != mario->dx)
            {
                if(mario->x + testDX <= (SIRINAPROZORA / 2 - mario->width / 2))
                    mario->x += testDX;
                else
                    break;
                totalDX += testDX;
            }
        }
        else
        {
            // walk in place
        }

        if(mario->objectY != 3)
        {
            mario->objectX++;
            if(mario->objectX == 2)
                mario->objectX = 0;
        }
//        mario->setWalkRight();
    }
    else if(PRITISNUTO(VK_LEFT))
    {
        mario->stateX = LEFT;
        if(background->x > 0 && mario->x == (SIRINAPROZORA / 2 - mario->width / 2))
        {
            int totalDX = 0;
            int testDX = -1;
            while(totalDX != -mario->dx)
            {
                if(UpdatePositionOfObjects(testDX, 0))
                    mario->startingX += -testDX; // za koliko revertati u slucaju da treba da se reverta
                else
                    break;
                totalDX += testDX;
            }
//            foreground.x -= mario->dx;
        }
        else if(mario->x + 10 > 0)
        {
            int totalDX = 0;
            int testDX = -1;
            while(totalDX != -mario->dx)
            {
                if(mario->x + testDX + 10 > 0)
                    mario->x += testDX;
                else
                    break;
                totalDX += testDX;
            }
        }
        else
        {
            //just walk in place
        }
//        mario->setWalkLeft();

        if(mario->objectY != 3)
        {
            mario->objectX++;
            if(mario->objectX == 2)
                mario->objectX = 0;
        }
    }
    else
    {
        mario->stateX = NEUTRAL;
        mario->objectX = 0;
    }

    if(PRITISNUTO(VK_SHIFT))
    {
    }
}

void Game::Render(void)
{
    GetClientRect(hwnd, clientRect);
    HDC hdc = GetDC(hwnd);

    DrawObjekat(hdc);
    ReleaseDC(hwnd, hdc);
}

void Game::Update(void)
{
    GetClientRect(hwnd, clientRect);
    UpdateObjekat();
}

bool Game::UpdatePositionOfObjects(int dx, int dy) // relative to obj (for example Mario)
{
    for(const auto& el : *objects)
    {
        el->x -= dx;
        el->startingX -= dx;
        el->y += dy;
        el->startingY += dy;
    }

    for(const std::shared_ptr<Object>& el : *objects) // provjerava za sve objekte da li ce se mario sudariti sa nima ukoliko se pomjeri za dx, dy
    {
        if(el->checkX(mario, dx) || el->checkY(mario, dy)) // ako ce se sudariti sa nekim govorimo pozivaocu da ne mozemo odraditi pomjeranje
        {
            return false;
        }
    }

    background->x += dx;
    background->y += dy;

    return true;
}

void Game::GenerateObjects()
{
    std::shared_ptr<Pipe> pipePtr = nullptr;
    objects->push_back(std::make_shared<QuestionBlock>(176, 201));
    objects->push_back(std::make_shared<QuestionBlock>(193, 201));
    objects->push_back(std::make_shared<QuestionBlock>(224, 153));
    objects->push_back(std::make_shared<QuestionBlock>(240, 153));
    objects->push_back(std::make_shared<QuestionBlock>(416, 169));
    objects->push_back(std::make_shared<QuestionBlock>(120, 201));
    pipePtr = std::make_shared<Pipe>(335, 240, objects, movingObjects);
    objects->push_back(pipePtr);
    objects->push_back(std::make_shared<Ground>(25, 200));
}

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
        if(el->hbm_ == NULL || el->hbmMask_ == NULL)
            continue;

        el->draw(hdcBuffer, hdcMem);

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

    for(std::shared_ptr<Object>& el : *movingObjects)
    {
        if(el->hbm_ == NULL || el->hbmMask_ == NULL)
            continue;

        el->draw(hdcBuffer, hdcMem);

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

void Game::UpdateObjekat() // Checking for interactions
{
    for(const std::shared_ptr<Object>& el : *objects)
    {
        if(distanceBetweenObjects(mario.get(), el.get()) > 120)
        {
            continue;
        }

        int marioDirection;
        int testMarioY = mario->y;
        int marioEndPoint = mario->y - mario->dy; // endPoint in this iteration of verifying if and where Mario is going to hit
        if(mario->dy == 0)
            marioDirection = 0; // more like marioYDirection
        else
        {
            marioDirection = mario->dy/abs(mario->dy); // -1 or +1, normirani vektor
        }

        do
        {
            if(!el->checkY(mario, testMarioY))
                break;
            testMarioY += marioDirection;
        }
        while(testMarioY != marioEndPoint);
    }
//    if((mario->stateY == DOWN) && (mario->ground != initial_ground.y) && (mario->y < initial_ground.y))
//    {
//        std::cout << "free fall\n";
////        std::cout << "-------------------------------------------------------------\n";
////        std::cout << "entering free fall\n" << "ground.y: " << ground.y << "initial_ground.y: " << initial_ground.y << std::endl;
////        std::cout << "-------------------------------------------------------------\n";
//        mario->ground = initial_ground.y;
//        mario->stateY = DOWN;
//    }

    praviUpdate();
}

void Game::praviUpdate() // Updating position of objects relative to Mario and Mario
{
//    std::cout << "-----------------------------------------------------------\n";
//    std::cout << "praviUpdate\nmario.dy: " << mario->dy << std::endl;
//    std::cout << "-----------------------------------------------------------\n";

//    static bool marioFocus = false;
    int totalDY = 0;
    int testDY;
    if(mario->dy == 0)
        testDY = 0;
    else
        testDY = mario->dy/abs(mario->dy);
    while(totalDY != mario->dy)
    {
        if(mario->y < (VISINAPROZORA/2 - mario->height/2 - 10))
        {
            std::cout << mario->y << std::endl;
            mario->ground += testDY;
            initial_ground += testDY;
            if(mario->y >= mario->ground)
            {
                int dist = mario->y - mario->ground;
                mario->ground = mario->y;
                initial_ground += dist;
                UpdatePositionOfObjects(0, dist);
                mario->objectY = 1;
            }
            UpdatePositionOfObjects(0, testDY);
            if((initial_ground - background->y + 211) < VISINAPROZORA)
            {
                int dist = VISINAPROZORA - 211 - initial_ground + background->y;
                UpdatePositionOfObjects(0, dist/2);
                if(testDY < 0)
                {
                    std::cout << "mario nanize\n";
                    mario->y += 1;
                }
            }
        }
        else if((mario->y + mario->height/2) >= (VISINAPROZORA/2 - 10))
        {
//        std::cout << "mario focus\ninitial_ground: " << initial_ground.y << std::endl;
//            static int correctionError;
//            if(initial_ground.typeOfObject != DEATHGROUND)
//            {
//                correctionError = 0;
//            }
//            else
//            {
//                correctionError = 16;
//            }
            if((initial_ground - background->y + 211) != (VISINAPROZORA))
            {
                int dist;
                dist = VISINAPROZORA - 211 - initial_ground + background->y;
                UpdatePositionOfObjects(0, dist/2);
//                return;
            }
            mario->y -= testDY;
            if(mario->y >= mario->ground) // da ne bi Mario propao kroz zemlju
            {
                mario->y = mario->ground;
                mario->objectY = 1;
            }
        }
        else
        {
            std::cout << "SOMETHIHG WENT WRONG!!\n";
            system("pause");
        }
        totalDY += testDY;
    }
    mario->dy -= 3;
    if(mario->dy < 0)
        mario->stateY = DOWN;
    else if(mario->dy > 0)
        mario->stateY = UP;
    else
        mario->stateY = NEUTRAL;

//    std::cout << "-------------------------------------------------------------\n";
//    std::cout << "Nakon updatea mario->y: " << mario->y << std::endl;
//    std::cout << "-------------------------------------------------------------\n";
    for(const std::shared_ptr<Object>& el : *objects)
    {
        if((el->typeOfObject == COIN) && (el->cycles == (el->cyclesUntilDeath/2)))
        {
            el->dy = -el->dy;
        }

//        int testingObjectY = el->y;
//        int directionY = el->dy/abs(el->dy);
//        int endPointY = el->y + el->dy;
//        while(testingObjectY != endPointY)
//        {
//            if((el->typeOfObject == QUESTIONMARK) && (el->y < el->startingY) && (el->flag))
//            {
//                el->dy += 2;
//            }
//            if((el->typeOfObject == QUESTIONMARK) && (el->y > el->startingY) && (el->flag))
//            {
////            std::cout << "stop\n";
//                el->dy = 0;
//                el->y = el->startingY;
//            }
//            testingObjectY += directionY;
//        }

        if((el->typeOfObject == QUESTIONMARK) && (el->y < el->startingY) && (el->flag))
        {
//            std::cout << el->dy << std::endl;
            el->dy += 3;
            if((el->y + el->dy) >= el->startingY)
            {
                el->dy = 0;
                el->y = el->startingY;
            }
        }

        if(el->typeOfObject == FLOWER_ENEMY)
        {
//            static HWND hwnd = GetForegroundWindow();
            if(el->y < el->startingY - 38)
            {
                std::cout << "flower_enemy reached peak" << std::endl;
                HWND hwnd = GetForegroundWindow();
                el->dy = 0;
                el->y = el->startingY - 38;
                SetTimer(hwnd, (UINT_PTR)el.get(), 3000, (TIMERPROC)&PiranhaTimerUp);
                std::cout << "UpTimer" << std::endl;
            }
            else if(el->y > el->startingY)
            {
                std::cout << "flower_enemy reached through" << std::endl;
                HWND hwnd = GetForegroundWindow();
                el->dy = 0;
                el->y = el->startingY;
                el->flag = false; // piranha is not active
                SetTimer(hwnd, (UINT_PTR)el.get(), 4500, (TIMERPROC)&PiranhaTimerDown);
                std::cout << "DownTimer" << std::endl;
            }
        }





        if((el->typeOfObject == GOOMBA) || (el->typeOfObject == FLOWER_ENEMY))
        {
            int testingObjectY = el->y;
            int directionY = el->dy/abs(el->dy);
            int endPointY = el->y + el->dy;
            while(testingObjectY != endPointY)
            {
                if((el->typeOfObject == FLOWER_ENEMY) && (el->flag == true) && (mario->stateY != UP) && ((mario->x + mario->leftSide) < (el->x + el->rightSide)) && ((mario->x + mario->rightSide) > (el->x + el->leftSide)) && ((mario->y + mario->bottomSide) == (testingObjectY + el->topSide)))
                {
                    std::cout << "2hit flower_enemy top side: " << mario->y << " " << (testingObjectY + el->topSide) << std::endl;
                    Render();
                    system("pause");
                    break;
                }
                else if((el->typeOfObject == FLOWER_ENEMY) && (el->flag == true) && ((mario->x + mario->leftSide) < (el->x + el->rightSide)) && ((mario->x + mario->rightSide) > (el->x + el->leftSide)) && ((mario->y + mario->topSide) == (testingObjectY + el->bottomSide)))
                {
                    std::cout << "2hit flower_enemy bottom side(why?)\n";
                    Render();
                    system("pause");
                    break;
                }
                testingObjectY += directionY;
            }
            el->x += el->dx;
            el->y += (testingObjectY - el->y);
        }
        else
        {
            el->x += el->dx;
            el->y += el->dy;
        }

        if(el->cyclesUntilDeath != -1)
        {
            ++el->cycles;
            std::cout << "Only dying coin should print this: " << el->cycles << std::endl;
        }

        if(el->cyclesUntilDeath == el->cycles)
        {
            objects->erase(partition(std::begin(*objects), end(*objects),
                                     [&el](const std::shared_ptr<Object> &x)
            {
                return x.get() == el.get();
            }),
            std::end(*objects));
//            objects->erase(std::remove(objects->begin(), objects->end(), *el), objects->end());
        }



//        if(el->typeOfObject == FLOWER_ENEMY)
//            std::cout << "flower_enemy.y: " << el->y << std::endl;
    }
}

