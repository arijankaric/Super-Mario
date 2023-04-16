#include "../include/Game.hpp"

void Game::UpdateObjekat() // Checking for interactions
{
//    for(const std::shared_ptr<Object>& el : *objects)
//    {
////        std::cout << el->getStringTypeOfObject(el) << std::endl;
////        if(distanceBetweenObjects(mario.get(), el.get()) > 120)
////        {
////            continue;
////        }
//
//        int marioDirectionY;
//        mario->testingY = mario->y;
//        int marioEndPoint = mario->y + mario->dy_; // endPoint in this iteration of verifying if and where Mario is going to hit
//        if(mario->dy_ == 0)
//        {
//            break;
//            marioDirectionY = 0; // more like marioYDirection
//        }
//        else
//        {
//            marioDirection = mario->dy_/abs(mario->dy_); // -1 or +1, normirani vektor
//        }
//
//        do
//        {
////            std::cout << "marioDirection: " << marioDirection << std::endl;
//            if(el->checkY(mario, marioDirection))
//            {
////                std::cout << el->getStringTypeOfObject(el) << " breaking on mario->testingY: " << mario->testingY << std::endl;
//                praviUpdate();
//                return;
//            }
//            mario->testingY += marioDirection;
////            std::cout << "mario->testingY: " << mario->testingY << std::endl;
//        }
//        while(mario->testingY != marioEndPoint);
//    }
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
//    std::cout << "praviUpdate\nmario.dy_: " << mario->dy_ << std::endl;
//    std::cout << "-----------------------------------------------------------\n";

//    static bool marioFocus = false;
//    mario->testingY = mario->y;
    mario->projectY();
//    std::cout << mario->y << " " << mario->dy_ << std::endl;
    int totaldy_ = mario->dy_;
    int testdy_ = 0;
    int directionY;
    if(mario->dy_ == 0)
        directionY = 0;
    else
        directionY = mario->dy_/abs(mario->dy_);
    while(totaldy_ != testdy_)
    {
        if(mario->y < (VISINAPROZORA/2 - mario->height/2))
        {
//            mario->ground -= testdy_;
//            initial_ground -= testdy_;
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
//            initial_ground += testdy_;
            UpdatePositionOfObjects(0, directionY);
            if((background->height - background->y - initial_ground) < VISINAPROZORA)
            {
                int dist = VISINAPROZORA + initial_ground - background->height + background->y;
                if(directionY > 0)
                {
                    std::cout << "mario nanize\n";
//                    mario->changeY(1);
                    mario->y += 1;
                }
                UpdatePositionOfObjects(0, -dist);
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
                UpdatePositionOfObjects(0, -dist);
//                return;
            }
//            std::cout << "mario->y: " << mario->y << std::endl;
            mario->y += directionY;
//            std::cout << "mario->y: " << mario->y << std::endl;
//            std::cout << "mario->stateY: " << mario->stateY << std::endl;
//            if((mario->y >= mario->ground) && (mario->stateY == NEUTRAL)) // da ne bi Mario propao kroz zemlju
//            {
//                std::cout << "mario ne propada kroz zemlju\n";
//                mario->y = mario->ground;
//                mario->objectY = 1;
//                mario->dy_ = 0;
//                break;
//            }
        }
        else
        {
            std::cout << "SOMETHIHG WENT WRONG!! opcija 3\n";
            system("pause");
        }
        testdy_ += directionY;
    }
//    mario->dy_ += 3;
    mario->nextdy_();
//    if(mario->dy_ < 0)
//    {
//        mario->setYState(Object::stateY::Up);
//    }
//    else if(mario->dy_ > 0)
//    {
//        mario->setYState(Object::stateY::Down);
//    }
//    else
//    {
//        mario->setYState(Object::stateY::Neutral);
//    }



//    std::cout << "-------------------------------------------------------------\n";
//    std::cout << "Nakon updatea mario->y: " << mario->y << std::endl;
//    std::cout << "-------------------------------------------------------------\n";
    for(const std::shared_ptr<Object>& el : *objects)
    {
        if((el == mario) || (distanceBetweenObjects(mario.get(), el.get()) > VISINAPROZORA))
        {
            continue;
        }

        if((el->cyclesUntilDeath == -2) && (distanceBetweenObjects(mario.get(), el.get()) > VISINAPROZORA))
        {
            el->removeDeadObject(el);
            return;
        }

        el->moveYX();
//        int testingObjectY = el->y;
//        int directionY = el->dy_/abs(el->dy_);
//        int endPointY = el->y + el->dy_;
//        while(testingObjectY != endPointY)
//        {
//            if((el->typeOfObject == QUESTIONMARK) && (el->y < el->startingY) && (el->flag))
//            {
//                el->dy_ += 2;
//            }
//            if((el->typeOfObject == QUESTIONMARK) && (el->y > el->startingY) && (el->flag))
//            {
////            std::cout << "stop\n";
//                el->dy_ = 0;
//                el->y = el->startingY;
//            }
//            testingObjectY += directionY;
//        }


//        if(el->typeOfObject == FLOWER_ENEMY)
//            std::cout << "flower_enemy.y: " << el->y << std::endl;
    }
//    std::cout << "mario->y: " << mario->y << " mario->dy_: " << mario->dy_ << std::endl;
}
