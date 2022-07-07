#include "Game.hpp"

void Game::UpdateObjekat() // Checking for interactions
{
    for(const std::shared_ptr<Object>& el : *objects)
    {
//        std::cout << el->getStringTypeOfObject(el) << std::endl;
//        if(distanceBetweenObjects(mario.get(), el.get()) > 120)
//        {
//            continue;
//        }

        int marioDirection;
        mario->testingY = mario->y;
        int marioEndPoint = mario->y + mario->dy; // endPoint in this iteration of verifying if and where Mario is going to hit
        if(mario->dy == 0)
            marioDirection = 0; // more like marioYDirection
        else
        {
            marioDirection = mario->dy/abs(mario->dy); // -1 or +1, normirani vektor
        }

        do
        {
//            std::cout << "marioDirection: " << marioDirection << std::endl;
            if(el->checkY(mario, marioDirection))
            {
//                std::cout << el->getStringTypeOfObject(el) << " breaking on mario->testingY: " << mario->testingY << std::endl;
                praviUpdate();
                return;
            }
            mario->testingY += marioDirection;
//            std::cout << "mario->testingY: " << mario->testingY << std::endl;
        }
        while(mario->testingY != marioEndPoint);
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

//    std::cout << "prije pravog Updatea\n";
    praviUpdate();
}

void Game::praviUpdate() // Updating position of objects relative to Mario and Mario
{
//    std::cout << "-----------------------------------------------------------\n";
//    std::cout << "praviUpdate\nmario.dy: " << mario->dy << std::endl;
//    std::cout << "-----------------------------------------------------------\n";

//    static bool marioFocus = false;
//    mario->testingY = mario->y;
    int totalDY = 0;
    int testDY;
    if(mario->dy == 0)
        testDY = 0;
    else
        testDY = mario->dy/abs(mario->dy);
    while(totalDY != mario->dy)
    {
        if(mario->y < (VISINAPROZORA/2 - mario->height/2))
        {
//            mario->ground -= testDY;
//            initial_ground -= testDY;
//            if(mario->y >= mario->ground)
//            {
//                int dist = mario->y - mario->ground;
//                mario->ground = mario->y;
////                initial_ground += dist;
//                mario->objectY = 1;
//                bool test = !UpdatePositionOfObjects(0, dist);
//                if(test)
//                    break;
//            }
//            initial_ground += testDY;
            UpdatePositionOfObjects(0, testDY);
            if((background->height - background->y - initial_ground) < VISINAPROZORA)
            {
                int dist = VISINAPROZORA + initial_ground - background->height + background->y;
                if(testDY > 0)
                {
                    std::cout << "mario nanize\n";
                    mario->y += 1;
                }
                if(!UpdatePositionOfObjects(0, -dist))
                    break;
            }
        }
        else if((mario->y + mario->height/2) >= (VISINAPROZORA/2))
        {
//            std::cout << "opcija1\n";
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
//            std::cout << "mario->y: " << mario->y << " mario->ground: " << mario->ground << std::endl;
//            system("pause");
//            std::cout << "initial_ground - background->y" << initial_ground - background->y << std::endl;
//            this->y = this->height - VISINAPROZORA - 155;
            if((background->height - background->y - initial_ground) != (VISINAPROZORA))
            {
                int dist;
                dist = VISINAPROZORA - background->height + background->y + initial_ground;
//                initial_ground += dist/2;
//                mario->ground += -dist;
                std::cout << "dist: " << dist << std::endl;
                if(!UpdatePositionOfObjects(0, -dist))
                    break;
//                return;
            }
//            std::cout << "mario->y: " << mario->y << std::endl;
            mario->y += testDY;
//            std::cout << "mario->y: " << mario->y << std::endl;
//            std::cout << "mario->stateY: " << mario->stateY << std::endl;
//            if((mario->y >= mario->ground) && (mario->stateY == NEUTRAL)) // da ne bi Mario propao kroz zemlju
//            {
//                std::cout << "mario ne propada kroz zemlju\n";
//                mario->y = mario->ground;
//                mario->objectY = 1;
//                mario->dy = 0;
//                break;
//            }
        }
        else
        {
            std::cout << "SOMETHIHG WENT WRONG!! opcija 3\n";
            system("pause");
        }
        totalDY += testDY;
    }
    mario->dy += 3;

    if(mario->dy < 0)
        mario->stateY = UP;
    else if(mario->dy > 0)
    {
        mario->stateY = DOWN;
    }
    else
        mario->stateY = NEUTRAL;



//    std::cout << "-------------------------------------------------------------\n";
//    std::cout << "Nakon updatea mario->y: " << mario->y << std::endl;
//    std::cout << "-------------------------------------------------------------\n";
    for(const std::shared_ptr<Object>& el : *objects)
    {
        el->moveYX(mario, true);
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


//        if(el->typeOfObject == FLOWER_ENEMY)
//            std::cout << "flower_enemy.y: " << el->y << std::endl;
    }
//    std::cout << "mario->y: " << mario->y << " mario->dy: " << mario->dy << std::endl;
}
