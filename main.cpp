#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <iostream>
#include "Game.hpp"

const int ID_TIMER = 1;
const int IDT_TIMER3 = 50;
const int ID_TIMER_PIRANHA_UP = 0;
const int ID_TIMER_PIRANHA_DOWN = 1;

const int DX = 1;
const int DY = 1;

//HBITMAP hbmMarioWalk;
//HBITMAP hbmMarioWalkMask;
//
//HBITMAP hbmMarioWalkLeft;
//HBITMAP hbmMarioWalkLeftMask;
//
//HBITMAP hbmMarioWalkRight;
//HBITMAP hbmMarioWalkRightMask;
//
//HBITMAP hbmBackground;
//HBITMAP hbmBackgroundMask;
//
//HBITMAP hbmForeground;
//HBITMAP hbmForegroundMask;
//
//HBITMAP enemy = (HBITMAP) LoadImage(NULL, "enemy.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//HBITMAP enemyMask = (HBITMAP) LoadImage(NULL, "enemyBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//
//HBITMAP questionMark = (HBITMAP) LoadImage(NULL, "QuestionMarkBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//HBITMAP questionMarkMask = (HBITMAP) LoadImage(NULL, "QuestionMark.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//
//HBITMAP coin = (HBITMAP) LoadImage(NULL, "Coin.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//HBITMAP coinMask = (HBITMAP) LoadImage(NULL, "CoinBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//
//HBITMAP goomba = (HBITMAP) LoadImage(NULL, "goomba.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//HBITMAP goombaMask = (HBITMAP) LoadImage(NULL, "goombaBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//
//HBITMAP ground = (HBITMAP) LoadImage(NULL, "ground.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//HBITMAP groundMask = (HBITMAP) LoadImage(NULL, "groundBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

//HBITMAP hill = (HBITMAP) LoadImage(NULL, "hill.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//HBITMAP hillMask = (HBITMAP) LoadImage(NULL, "hillBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
               0,                   /* Extended possibilites for variation */
               szClassName,         /* Classname */
               _T("Code::Blocks Template Windows App"),       /* Title Text */
               (WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MINIMIZEBOX ^ WS_SYSMENU), /* default window */
               700,       /* Windows decides the position */
               300,       /* where the window ends up on the screen */
               SIRINAPROZORA,                 /* The programs width */
               VISINAPROZORA,                 /* and height in pixels */
               HWND_DESKTOP,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );
    Game game1;
    game1.hwnd = hwnd;

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

//    Initalize(hwnd);
    DWORD vrijeme_pocetak;

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (TRUE)
    {

        if(PeekMessage(&messages, NULL, 0,0, PM_REMOVE))
        {
            if(messages.message == WM_QUIT)
            {
                break;
            }
            TranslateMessage(&messages);
            DispatchMessage(&messages);
        }

        vrijeme_pocetak = GetTickCount(); // DWORD GetTickCount(); The return value is the number of milliseconds that have elapsed since the system was started.

        game1.CheckInput();
//        std::cout << "checkInput izvrsen\n";
        game1.Update();
//        std::cout << "update izvrsen\n";
        game1.Render();
//        std::cout << "render izvrsen\n";

        while(GetTickCount()- vrijeme_pocetak < 16.66666666666667) // 1000/60 = 16.66666666666667; 55 prethodna vrijednost
        {
//            std::cout << "sleep(1)" << std::endl;
            Sleep(1);
        }
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
    case WM_DESTROY:
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    case WM_TIMER:
        std::cout << "WM_TIMER wParam: " << wParam << std::endl;
        switch (wParam)
        {
        case ID_TIMER_PIRANHA_UP:
            std::cout << "PIRANHA_UP_TIMER\n";
            KillTimer(hwnd, ID_TIMER_PIRANHA_UP);
            return 0;

        case ID_TIMER_PIRANHA_DOWN:
            std::cout << "PIRANHA_DOWN_TIMER\n";
            KillTimer(hwnd, ID_TIMER_PIRANHA_DOWN);
            return 0;
        }
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

//void UpdateObjekat(HWND hwnd, RECT* rect) // Checking for interactions
//{
////    initial_ground = whereInitialGround(background->x);
//    for(const std::shared_ptr<Object>& el : *objects)
//    {
//        if(distanceBetweenObjects(mario.get(), el.get()) > 120)
//        {
//            continue;
//        }
//
//        int marioDirection;
//        int testMarioY = mario->y;
//        int marioEndPoint = mario->y - mario->dy; // endPoint in this iteration of verifying if and where Mario is going to hit
//        if(mario->dy == 0)
//            marioDirection = 0; // more like marioYDirection
//        else
//        {
//            marioDirection = mario->dy/abs(mario->dy); // -1 or +1, normirani vektor
//        }
//
////        if(marioDirection < 0)
////        {
//////            std::cout << "-------------------------------------------------------------\n";
//////            std::cout << "incrementMarioEndPoint\n";
//////            std::cout << "-------------------------------------------------------------\n";
////            ++testMarioY;
////        }
////        else if(marioDirection > 0)
////        {
//////            std::cout << "-------------------------------------------------------------\n";
//////            std::cout << "decrementMarioEndPoint\n";
//////            std::cout << "-------------------------------------------------------------\n";
////            --testMarioY;
////        }
////        else
////        {
////            //marioEndPoint stays the same
////        }
//
//        do
//        {
////            if(mario->stateY == DOWN)
////                std::cout << "DOWN\n";
////            else if(mario->stateY == UP)
////                std::cout << "UP\n";
////            else if(mario->stateY == NEUTRAL)
////                std::cout << "NEUTRAL\n";
////            else
////                std::cout << "WHY?\n";
////            std::cout << "-------------------------------------------------------------\n";
////            std::cout << "testMarioY petlja\ntestMarioY: " << testMarioY << "\nmarioDirection: " << marioDirection << "\nmario.dy: " << mario->dy << "\nmarioEndPoint:" << marioEndPoint << std::endl;
////            std::cout << "-------------------------------------------------------------\n";
//            if((el->typeOfObject == QUESTIONMARK) && (mario->stateY != UP) && ((mario->x + mario->leftSide) < (el->x + el->rightSide)) && ((mario->x + mario->rightSide) > (el->x + el->leftSide)) && ((testMarioY + mario->bottomSide) == (el->y + el->topSide)))
//            {
////                std::cout<< "hit new(questionMark) ground\n";
//                mario->stateY = NEUTRAL;
//                mario->dy = mario->y - testMarioY;
//                mario->ground = testMarioY;
//                mario->objectY = 1;
//                break;
//            }
//            else if((el->typeOfObject == PIPE) && (mario->stateY != UP) && ((mario->x + mario->leftSide) < (el->x + el->rightSide)) && ((mario->x + mario->rightSide) > (el->x + el->leftSide)) && ((testMarioY + mario->bottomSide) == (el->y + el->topSide)))
//            {
////                std::cout << testMarioY << std::endl;
//                std::cout << "hit top side of pipe\n";
//                mario->stateY = NEUTRAL;
////                el->flag = true;
//                mario->dy = mario->y - testMarioY;
////                mario->dy = 0;
//                mario->ground = testMarioY;
//                mario->objectY = 1;
//                break;
//            }
//            else if((el->typeOfObject == QUESTIONMARK) && (mario->stateY == UP) && ((mario->x + mario->leftSide) < (el->x + el->rightSide)) && ((mario->x + mario->rightSide) > (el->x + el->leftSide)) && ((testMarioY + mario->topSide) == (el->y + el->bottomSide)) && (marioDirection > 0))
//            {
//                mario->stateY = DOWN;
//                mario->dy = (mario->y - testMarioY - 1);
////                std::cout << "mario->dy: " << mario->dy << std::endl;
////                std::cout << "-------------------------------------------------------------\n";
////                std::cout << "hit question mark\n";
////                std::cout << "-------------------------------------------------------------\n";
//                if(!el->flag)
//                {
////                    std::cout << "-------------------------------------------------------------\n";
////                    std::cout << "hit full question mark\n";
////                    std::cout << "-------------------------------------------------------------\n";
//                    el->dy = -8;
//                    el->flag = true;
////                    el->startingY = el->y;
//                    el->hbm_ = (HBITMAP) LoadImage(NULL, "emptyQuestionBlockBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//                    el->hbmMask_ = (HBITMAP) LoadImage(NULL, "emptyQuestionBlock.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//                    el->max = 1;
//
////                    GenerateCoin(el->x, el->y, true);
//                }
////                std::cout << "-------------------------------------------------------------\n";
////                std::cout << "mario->y-mario->dy: " << mario->y-mario->dy << "\ntestMarioY: " << testMarioY << std::endl;
////                std::cout << "-------------------------------------------------------------\n";
//                praviUpdate(hwnd);
//                Render(hwnd);
//
//
//                mario->dy = -12;
//                return;
//            }
//            else if((el->typeOfObject == FLOWER_ENEMY) && (el->flag == true) && (mario->stateY != UP) && ((mario->x + mario->leftSide) < (el->x + el->rightSide)) && ((mario->x + mario->rightSide) > (el->x + el->leftSide)) && ((testMarioY + mario->bottomSide) == (el->y + el->topSide)))
//            {
//                mario->dy = mario->y - testMarioY;
//                std::cout << "hit flower_enemy top side: " << testMarioY << " " << (mario->y - mario->dy) << " " << (el->y + el->topSide) << std::endl;
//                praviUpdate(hwnd);
//                Render(hwnd);
//                system("pause");
//                break;
//            }
//            else if((el->typeOfObject == FLOWER_ENEMY) && (el->flag == true) && ((mario->x + mario->leftSide) < (el->x + el->rightSide)) && ((mario->x + mario->rightSide) > (el->x + el->leftSide)) && ((testMarioY + mario->topSide) == (el->y + el->bottomSide)))
//            {
//                std::cout << "hit flower_enemy bottom side(why?)\n";
//                praviUpdate(hwnd);
//                Render(hwnd);
//                system("pause");
//                break;
//            }
//            else if((el->typeOfObject == GROUND) && ((mario->x + mario->leftSide) < (el->x + el->rightSide)) && ((mario->x + mario->rightSide) > (el->x + el->leftSide)) && ((testMarioY + mario->topSide) == (el->y + el->bottomSide)))
//            {
//                std::cout << "hit bottom of ground: " << testMarioY << std::endl;
//                mario->stateY = DOWN;
//                mario->dy = (mario->y - testMarioY - 2);
////                praviUpdate(hwnd);
////                Render(hwnd);
////                mario->dy = -5;
////                system("pause");
//                break;
//            }
//            else if((el->typeOfObject == GROUND) && ((mario->x + mario->leftSide) < (el->x + el->rightSide)) && ((mario->x + mario->rightSide) > (el->x + el->leftSide)) && ((testMarioY + mario->bottomSide) == (el->y + el->topSide)))
//            {
//                std::cout << "hit top of ground: " << testMarioY << std::endl;
//                mario->dy = (mario->y - testMarioY);
//                mario->ground = testMarioY + mario->bottomSide;
//                mario->objectY = 1;
//                break;
//            }
//            testMarioY -= marioDirection;
//        }
//        while(testMarioY != marioEndPoint);
//    }
////    if((mario->stateY == DOWN) && (mario->ground != initial_ground.y) && (mario->y < initial_ground.y))
////    {
////        std::cout << "free fall\n";
//////        std::cout << "-------------------------------------------------------------\n";
//////        std::cout << "entering free fall\n" << "ground.y: " << ground.y << "initial_ground.y: " << initial_ground.y << std::endl;
//////        std::cout << "-------------------------------------------------------------\n";
////        mario->ground = initial_ground.y;
////        mario->stateY = DOWN;
////    }
//
//
//
////    if(mario->dy > 0)
////    {
////        mario->dy -= 3;
////
////    }
////    else
////    {
////        mario->dy -= 3;
////    }
////    if(mario->dy == -8)
////        system("pause");
//
//
////    if(mario->dy < -17)
////    {
////        mario->dy = -17;
////    }
//
//
////    mario->y += mario->dy;
//
//    praviUpdate(hwnd);
//}
//
////bool UpdatePositionOfObjects(int dx, int dy) // relative to Mario
////{
//////    initial_ground = whereInitialGround(background->x);
////    for(const auto& el:objects)
////    {
//////        if((el->typeOfObject == PIPE) && ((mario->x + mario->rightSide) == (el->x + el->leftSide)) && ((mario->y + mario->bottomSide) <= (el->y + el->bottomSide)) && ((mario->y + mario->bottomSide) > (el->y + el->topSide)) && (dx > 0))
//////        {
//////            std::cout << "----------------------------------\n";
//////            std::cout << "hit left side of pipe\n";
//////            std::cout << "----------------------------------\n";
//////            return false;
//////        }
//////        else if((el->typeOfObject == PIPE) && ((mario->x + mario->leftSide) == (el->x + el->rightSide)) && ((mario->y + mario->bottomSide) <= (el->y + el->bottomSide)) && ((mario->y + mario->bottomSide) > (el->y + el->topSide)) &&  (dx < 0))
//////        {
//////            std::cout << "----------------------------------\n";
//////            std::cout << "hit right side of pipe\n";
//////            std::cout << "----------------------------------\n";
//////            return false;
//////        }
////////        (mario->x < (el->x + 2)) && (mario->x > (el->x - 20)) && (testMarioY == (el->y+6))
//////        else if((el->typeOfObject == QUESTIONMARK) && ((mario->x + mario->rightSide) == (el->x + el->leftSide)) && (((mario->y + mario->bottomSide) <= (el->y + el->bottomSide)) && ((mario->y + mario->bottomSide) > (el->y + el->topSide)) || ((mario->y + mario->topSide) <= (el->y + el->bottomSide)) && ((mario->y + mario->topSide) > (el->y + el->topSide))) && (dx > 0) )
//////        {
//////            std::cout << "----------------------------------\n";
//////            std::cout << "hit left side of questionmark\n";
//////            std::cout << "----------------------------------\n";
//////            return false;
//////        }
//////        else if((el->typeOfObject == QUESTIONMARK) && ((mario->x + mario->leftSide) == (el->x + el->rightSide)) && (((mario->y + mario->bottomSide) < (el->y + el->bottomSide)) && ((mario->y + mario->bottomSide) > (el->y + el->topSide)) || ((mario->y + mario->topSide) <= (el->y + el->bottomSide)) && ((mario->y + mario->topSide) > (el->y + el->topSide))))
//////        {
//////            std::cout << "----------------------------------\n";
//////            std::cout << "hit right side of questionmark\n";
//////            std::cout << "----------------------------------\n";
//////            return false;
//////        }
//////        else if((el->typeOfObject == FLOWER_ENEMY) && ((mario->x + mario->rightSide) == (el->x + el->leftSide)) && (((mario->y + mario->bottomSide) < (el->y + el->bottomSide)) && ((mario->y + mario->bottomSide) > (el->y + el->topSide)) || ((mario->y + mario->topSide) <= (el->y + el->bottomSide)) && ((mario->y + mario->topSide) > (el->y + el->topSide))) )
//////        {
//////            std::cout << "----------------------------------\n";
//////            std::cout << "hit left side of flower_enemy\n";
//////            std::cout << "----------------------------------\n";
//////            system("pause");
//////            return false;
//////        }
//////        else if((el->typeOfObject == FLOWER_ENEMY) && ((mario->x + mario->leftSide) == (el->x + el->rightSide)) && (((mario->y + mario->bottomSide) < (el->y + el->bottomSide)) && ((mario->y + mario->bottomSide) > (el->y + el->topSide)) || ((mario->y + mario->topSide) <= (el->y + el->bottomSide)) && ((mario->y + mario->topSide) > (el->y + el->topSide))))
//////        {
//////            std::cout << "----------------------------------\n";
//////            std::cout << "hit right side of flower_enemy\n";
//////            std::cout << "----------------------------------\n";
//////            system("pause");
//////            return false;
//////        }
//////        else if((mario->stateX != NEUTRAL) && (mario->y > initial_ground.y)) // ivicnjak, mario->state == WALKING(ubuduce)
//////        {
////////        std::cout << "hit higher ground\n";
////////            UpdatePositionOfObjects(mario->startingX, 0); // vrati ga za mario->startingDX, iskoristili smo polje startingX, ali polje treba da se zove startingDX, a ne startingX
//////            return false; // udario si u ivicnjak odnosno higher ground nema nikavog azuriranja, ostani tu gdje jesi
//////            // UpdatePositionOfObjects vraca na prvobitno pomjeranje
//////        }
//////        if( (mario->x < (el->x + 5)) && (mario->x > (el->x - 10)) && (mario->y < (el->y+15)) && (mario->y > (el->y-10)))
//////        {
//////            std::cout << "hit wall\n";
//////            return;
//////        }
////    }
//
//    background->x += dx;
//    background->y -= dy;
//
//    for(const auto& el:objects)
//    {
//        el->x -= dx;
//        el->y += dy;
//        el->startingY += dy;
//    }
//    return true;
//}

//void CheckInput(void)
//{
////    mario->state = UNKNOWN;
//    if(PRITISNUTO(VK_ESCAPE))
//    {
//        exit(0);
//    }
//
//    if(PRITISNUTO(VK_UP) && mario->objectY != 3 && mario->objectY != 4)
//    {
//        mario->stateY = UP;
//        mario->objectY = 3;
//        mario->objectX = 0;
//        mario->dy = 22;
////        if(mario->y <= (VISINAPROZORA/2-mario->height/2 - 10) && ((initial_ground.y - background->y + 211) >= VISINAPROZORA))
////        {
////            std::cout << "camera jumped up\n";
////            ground.y += mario->dy;
////            initial_ground.y += mario->dy;
////            UpdatePositionOfObjects(0, mario->dy);
////        }
////        else if(mario->y + mario->height/2  >= VISINAPROZORA/2 - 10)
////        {
////            std::cout << "mario jumped up\n";
////            mario->y -= mario->dy;
////        }
////        else
////        {
////            std::cout << "SOMETHING WENT WRONG 2\n";
////            // walk in place
////        }
//    }
////    else if(mario->y == initial_ground.y)
////    {
////        mario->stateY = NEUTRAL;
////    }
//
//    if(PRITISNUTO(VK_RIGHT))
//    {
//        mario->stateX = RIGHT;
//        if(background->x < (background->width - SIRINAPROZORA) && mario->x == (SIRINAPROZORA/2-mario->width/2))
//        {
//            uint16_t totalDX = 0;
//            uint16_t testDX = 1;
//            while(totalDX != mario->dx)
//            {
//                if(UpdatePositionOfObjects(testDX, 0))
//                    mario->startingX += - testDX; // more like mario->startingDX
//                else
//                    break;
//                totalDX += testDX;
//            }
////            foreground.x += mario->dx;
//        }
//        else if(mario->x < (SIRINAPROZORA / 2 - mario->width / 2)) // kad ode skroz na desno
//        {
//            uint16_t totalDX = 0;
//            uint16_t testDX = 1; // smoother walking("more precise")/updating
//            while(totalDX != mario->dx)
//            {
//                if(mario->x + testDX <= (SIRINAPROZORA / 2 - mario->width / 2))
//                    mario->x += testDX;
//                else
//                    break;
//                totalDX += testDX;
//            }
//        }
//        else
//        {
//            // walk in place
//        }
//
//        if(mario->objectY != 3)
//        {
//            mario->objectX++;
//            if(mario->objectX == 2)
//                mario->objectX = 0;
//        }
////        mario->setWalkRight();
//    }
//    else if(PRITISNUTO(VK_LEFT))
//    {
//        mario->stateX = LEFT;
//        if(background->x > 0 && mario->x == (SIRINAPROZORA / 2 - mario->width / 2))
//        {
//            int totalDX = 0;
//            int testDX = -1;
//            while(totalDX != -mario->dx)
//            {
//                if(UpdatePositionOfObjects(testDX, 0))
//                    mario->startingX += -testDX; // za koliko revertati u slucaju da treba da se reverta
//                else
//                    break;
//                totalDX += testDX;
//            }
////            foreground.x -= mario->dx;
//        }
//        else if(mario->x + 10 > 0)
//        {
//            int totalDX = 0;
//            int testDX = -1;
//            while(totalDX != -mario->dx)
//            {
//                if(mario->x + testDX + 10 > 0)
//                    mario->x += testDX;
//                else
//                    break;
//                totalDX += testDX;
//            }
//        }
//        else
//        {
//            //just walk in place
//        }
////        mario->setWalkLeft();
//
//        if(mario->objectY != 3)
//        {
//            mario->objectX++;
//            if(mario->objectX == 2)
//                mario->objectX = 0;
//        }
//    }
//    else
//    {
//        mario->stateX = NEUTRAL;
//        mario->objectX = 0;
//    }
//
//    if(PRITISNUTO(VK_SHIFT))
//    {
//    }
//}

//void Initalize(HWND hwnd)
//{
//    RECT clientRect;
//    GetClientRect(hwnd, &clientRect);
//
////    hbmBackground = (HBITMAP) LoadImage(NULL, "background->bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
////    hbmBackgroundMask = (HBITMAP) LoadImage(NULL, "backgroundBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//
////    hbmForeground = (HBITMAP) LoadImage(NULL, "mapFG.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
////    hbmForegroundMask = (HBITMAP) LoadImage(NULL, "mapFGBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//
//
////    hbmMarioWalkLeft = (HBITMAP) LoadImage(NULL, "SmallMarioLeft.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
////    hbmMarioWalkLeftMask = (HBITMAP) LoadImage(NULL, "SmallMarioLeftBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
////    hbmMarioWalkRight = (HBITMAP) LoadImage(NULL, "SmallMarioRight.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
////    hbmMarioWalkRightMask = (HBITMAP) LoadImage(NULL, "SmallMarioRightBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//
////    hbmMarioWalk = hbmMarioWalkRight;
////    hbmMarioWalkMask = hbmMarioWalkRightMask;
////
////    BITMAP bitmap;
////
////    GetObject(hbmBackground, sizeof(BITMAP), &bitmap);
////    background->width = bitmap.bmWidth;
////    background->height = bitmap.bmHeight;
////    background->x=0;
////    background->y=background->height - VISINAPROZORA - 155;
//
////    GetObject(hbmForeground, sizeof(BITMAP), &bitmap);
////    foreground.width = bitmap.bmWidth;
////    foreground.height = bitmap.bmHeight;
////    foreground.x = 0;
////    foreground.y = foreground.height - VISINAPROZORA + 75;
//
////    GetObject(hbmMarioWalk, sizeof(BITMAP), &bitmap);
////    mario->width = bitmap.bmWidth/3;
////    mario->height = bitmap.bmHeight/10;
////    mario->y = VISINAPROZORA - 80;
////    mario->x = SIRINAPROZORA/2-mario->width/2;
////    mario->dx = 5;
////    mario->bottomSide = 25;
////    mario->leftSide = 12;
////    mario->rightSide = 24;
////    mario->topSide = 10;
////    mario->outline = true;
////
////    mario->ground = mario->y;
//
////    initial_ground.y = 240;
////
////    initial_ground_first->y = 240;
////    initial_ground_second->y = 224;
////    initial_ground_third->y = 240;
////    death_ground->y = 256;
////    death_ground->typeOfObject = DEATHGROUND;
//
//
//    GenerateObjects(); // generates objects for World 1-1
//}

//void Update(HWND hwnd)
//{
//    RECT clientRect;
//    GetClientRect(hwnd, &clientRect);
//    UpdateObjekat(hwnd, &clientRect);
//}

//void Render(HWND hwnd)
//{
//    RECT clientRect;
//    GetClientRect(hwnd, &clientRect);
//    HDC hdc = GetDC(hwnd);
//
//    DrawObjekat(hdc, &clientRect);
//    ReleaseDC(hwnd, hdc);
//}

//Object whereInitialGround(int x)
//{
//
//
//    if(x < 500)
//    {
////        std::cout << "returning initial ground first\n";
////        std::cout << initial_ground_first->y << std::endl;
//        return *initial_ground_first;
//    }
//    else if(x < 970)
//    {
////        std::cout << "returning initial ground second\n";
////        std::cout << initial_ground_second->y << std::endl;
//        return *initial_ground_second;
//    }
//    else if(x < 1025)
//    {
//        std::cout << "returning death ground\n";
//        std::cout << death_ground->y << std::endl;
//        return *death_ground;
//    }
//    else if(x < 1500)
//    {
//        std::cout << "returning initial ground third\n";
//        std::cout << initial_ground_third->y << std::endl;
//        return *initial_ground_third;
//    }
//    else
//    {
//        std::cout << "returning initial ground 4(not covered yet)\n";
//        std::cout << initial_ground_third->y << std::endl;
//        return *initial_ground_third;
//    }
//}
