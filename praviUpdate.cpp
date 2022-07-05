#include "praviUpdate.hpp"

void praviUpdate(HWND hwnd) // Updating position of objects relative to Mario and Mario
{
//    std::cout << "-----------------------------------------------------------\n";
//    std::cout << "praviUpdate\nmario.dy: " << mario->dy << std::endl;
//    std::cout << "-----------------------------------------------------------\n";

//    static bool marioFocus = false;
    int totalDY = 0;
    int testDY = mario->dy/abs(mario->dy);
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
    for(const std::shared_ptr<Object>& el:objects)
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
                SetTimer(hwnd, (UINT_PTR)el.get(), 3000, (TIMERPROC) PiranhaTimerUp);
                std::cout << "UpTimer" << std::endl;
            }
            else if(el->y > el->startingY)
            {
                std::cout << "flower_enemy reached through" << std::endl;
                HWND hwnd = GetForegroundWindow();
                el->dy = 0;
                el->y = el->startingY;
                el->flag = false; // piranha is not active
                SetTimer(hwnd, (UINT_PTR)el.get(), 4500, (TIMERPROC) PiranhaTimerDown);
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
                    Render(hwnd);
                    system("pause");
                    break;
                }
                else if((el->typeOfObject == FLOWER_ENEMY) && (el->flag == true) && ((mario->x + mario->leftSide) < (el->x + el->rightSide)) && ((mario->x + mario->rightSide) > (el->x + el->leftSide)) && ((mario->y + mario->topSide) == (testingObjectY + el->bottomSide)))
                {
                    std::cout << "2hit flower_enemy bottom side(why?)\n";
                    Render(hwnd);
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
            objects.erase(std::remove(objects.begin(), objects.end(), el), objects.end());
        }



//        if(el->typeOfObject == FLOWER_ENEMY)
//            std::cout << "flower_enemy.y: " << el->y << std::endl;
    }
}
