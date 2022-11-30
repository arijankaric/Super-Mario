#include "Game.hpp"

Game::Game()
{
//    movingObjects->push_back(mario);
    objects->push_back(mario);
    // dodaj samo goombe u movingObjects?
    Object::mario = mario;
    Object::objects = objects;
    GenerateObjects();
}

void Game::CheckInput(void)
{
//    std::cout << "mario->dx: " << mario->dx << " mario->y: " << mario->y << std::endl;



    if(PRITISNUTO(VK_ESCAPE))
    {
        // implementirati pause mehaniku
        exit(0);
    }

    if(mario->life_ == 0)
    {
//        if(mario->cyclesUntilDeath > 6/2)
//        {
//            mario->y -= 1;
//        }
//        else
//        {
//            mario->y += 1;
//        }
        return;
    }

    if(PRITISNUTO(VK_UP))
    {
        mario->setYState(Object::stateY::Up);
//        mario->dy = -22;
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
        mario->setXState(Object::stateX::Right);
        mario->projectX();
        if(background->x < (background->width - SIRINAPROZORA) && (mario->centerX() >= SIRINAPROZORA/2))
        {
//            mario->x = (SIRINAPROZORA / 2);
            UpdatePositionOfObjects(mario->dx, 0);
//            uint16_t totalDX = 0;
//            uint16_t testDX = 1;
//            std::cout << "pokusava se kretati desno ali " << mario->dx << std::endl;
//            while(totalDX != mario->dx)
//            {
//                if(UpdatePositionOfObjects(testDX, 0))
//                    mario->startingX += - testDX; // more like mario->startingDX
//                else
//                    break;
//                totalDX += testDX;
//            }
        }
        else if(mario->x + mario->rightSide < SIRINAPROZORA) // kad ode skroz na desno
        {
            mario->x += mario->dx;
//            uint16_t totalDX = 0;
//            uint16_t testDX = 1; // smoother walking("more precise")/updating
//            while(totalDX != mario->dx)
//            {
//                if(mario->x + mario->rightSide + testDX < SIRINAPROZORA)
//                    mario->x += testDX;
//                else
//                    break;
//                totalDX += testDX;
//            }
        }
        else
        {
            std::cout << "walking in place on the right\nudaras u zid\n";
        }
    }
    else if(PRITISNUTO(VK_LEFT))
    {
        mario->setXState(Object::stateX::Left);
        mario->projectX();
//        (std::dynamic_pointer_cast<Mario>(mario))->setWalkLeft();
//        mario->stX_ = Object::stateX::Left;
//        mario->Y = 1;
        if(background->x > 0 && (mario->centerX() <= (SIRINAPROZORA / 2)))
        {
//            mario->x = (SIRINAPROZORA / 2);
            UpdatePositionOfObjects(mario->dx, 0);
//            int totalDX = 0;
//            int testDX = -1;
//            while(totalDX != mario->dx)
//            {
//                if(UpdatePositionOfObjects(testDX, 0))
//                    mario->startingX += -testDX; // za koliko revertati u slucaju da treba da se reverta
//                else
//                    break;
//                totalDX += testDX;
//            }
//            foreground.x -= mario->dx;
        }
        else if(mario->x + mario->leftSide > 0)
        {
            mario->x += mario->dx;
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
        }
        else
        {
            std::cout << "Mario is colliding with left end point\n";
            //just walk in place
        }
//        mario->setWalkLeft();

//        if(mario->objectY != 3)
//        {
//            mario->objectX++;
//            if(mario->objectX == 2)
//                mario->objectX = 0;
//        }
    }
    else
    {
        mario->setXState(Object::stateX::Neutral);
//        mario->stX_ = ;
//        mario->objectX = 0;
    }

    if(PRITISNUTO(VK_SHIFT))
    {
        // mario ubrzava/trci
    }
}

void Game::Render(void)
{
    GetClientRect(hwnd, clientRect);
    HDC hdc = GetDC(hwnd);

    DrawObjekat(hdc);
    ReleaseDC(hwnd, hdc);

    if((mario->life_ == 0) && (mario->getTop() > VISINAPROZORA))
    {
        std::cout << "Game Over. Mario dead\n";
        system("pause");
        // izgubio zivot - vraca na last checkpoint ili pocetak mape
        // izgubio sve zivote - vraca na meni/map selector ili nesto
    }
}

void Game::Update(void)
{
    GetClientRect(hwnd, clientRect);
    UpdateObjekat();
}

bool Game::UpdatePositionOfObjects(int dx, int dy) // relative to obj (for example Mario)
{
    background->x += dx;
    background->y += dy;

    mario->ground -= dy;

    for(const auto& el : *objects)
    {
        if(el == mario)
            continue;
        el->x -= dx;
        el->startingX -= dx;
        el->y -= dy;
        el->startingY -= dy;
    }

//    bool X = false;
//    bool Y = false;
//    for(const std::shared_ptr<Object>& el : *objects) // provjerava za sve objekte da li ce se mario sudariti sa nima ukoliko se pomjeri za dx, dy
//    {
//        if(el->checkX(mario, dx)) // ako ce se sudariti sa nekim govorimo pozivaocu da ne mozemo odraditi pomjeranje
//        {
//            std::cout << "Mario se sudara po x-u\n";
//            X = true;
//        }
//        if(el->checkY(mario, dy))
//        {
//            std::cout << "Mario se sudara po y-u\n";
//            Y = true;
//        }
//        if(X && Y)
//        {
//            return false;
//        }
//    }
//
//    if(!X)
//    {
////        std::cout << "UpdatePositionOfObjects dx: " << dx << std::endl;
//        background->x += dx;
//    }
//    if(!Y)
//    {
////        std::cout << "UpdatePositionOfObjects dy: " << dy << std::endl;
//        background->y += dy;
//    }
//
//
//    for(const auto& el : *objects)
//    {
//        if(!X)
//        {
//            el->x -= dx;
//            el->startingX -= dx;
//        }
//        if(!Y)
//        {
//            el->y -= dy;
//            el->startingY -= dy;
//        }
//    }
//    if(X && Y)
//        return false;
//
//    return true;
}

void Game::GenerateObjects()
{
    std::shared_ptr<Object> objPtr = nullptr;
    objects->push_back(std::make_shared<QuestionBlock>(176, 201));
    objects->push_back(std::make_shared<QuestionBlock>(193, 201));
    objects->push_back(std::make_shared<QuestionBlock>(224, 153));
    objects->push_back(std::make_shared<QuestionBlock>(240, 153));
    objects->push_back(std::make_shared<QuestionBlock>(416, 169));
    objects->push_back(std::make_shared<QuestionBlock>(120, 201));
    objPtr = std::make_shared<Pipe>(335, 240);
    objects->push_back(std::make_shared<FlowerEnemy>(359, 221, objPtr, FlowerEnemy::flowerType::thrower));
    objects->push_back(objPtr);
    objects->push_back(std::make_shared<Ground>(25, 200));

    objPtr = std::make_shared<Ground>(0, 264);
    objPtr->rightSide = 600;
    objPtr->leftSide = 0;
    objPtr->hbm_ = objPtr->hbmMask_ = nullptr;
    objects->push_back(objPtr);

    objPtr = std::make_shared<Ground>(272, 185, true);
    objPtr->rightSide = 47;
    objPtr->leftSide = 0;
    objPtr->hbm_ = objPtr->hbmMask_ = nullptr;
    objects->push_back(objPtr);

    objPtr = std::make_shared<Ground>(240, 215, true);
    objPtr->rightSide = 47;
    objPtr->leftSide = 0;
    objPtr->hbm_ = objPtr->hbmMask_ = nullptr;
    objects->push_back(objPtr);

//    objects->push_back(std::make_shared<Turtle>(245, 170));

//    objects->push_back(std::make_shared<FlowerEnemy>(objects, movingObjects, 359, 221, (TIMERPROC)&PiranhaTimerUp, (TIMERPROC)&PiranhaTimerDown));

    objects->push_back(std::make_shared<Goomba>(300, 250));
    objects->push_back(std::make_shared<Turtle>(40, 235));
//    objects->push_back(std::make_shared<Fireball>(mario->x, mario->y, -1, -1));
}

