#include "Game.hpp"

Game::Game()
{
    movingObjects->push_back(mario);
    GenerateObjects();
}

void Game::CheckInput(void)
{
//    std::cout << "mario->x: " << mario->x << " mario->y: " << mario->y << std::endl;
    mario->Y = 0;
//    mario->state = UNKNOWN;
    if(PRITISNUTO(VK_ESCAPE))
    {
        // implementirati pause mehaniku
        exit(0);
    }

//    std::cout << mario->stateY << std::endl;
// && mario->objectY != 3 && mario->objectY != 4
    if(PRITISNUTO(VK_UP) &&  (mario->y + mario->bottomSide == mario->ground))
    {
        mario->stateY = UP;
        mario->Y = 3;
        mario->X = 0;
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
//        std::shared_ptr<Mario> mario1 = std::dynamic_pointer_cast<Mario>(mario);
//        mario1->setWalkRight();
        mario->Y = 1;
        mario->stateX = RIGHT;
        (std::dynamic_pointer_cast<Mario>(mario))->setWalkRight();
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
            std::cout << "walking in place on the right\n";
            // walk in place
        }
//        mario->setWalkRight();
    }
    else if(PRITISNUTO(VK_LEFT))
    {
        (std::dynamic_pointer_cast<Mario>(mario))->setWalkLeft();
        mario->stateX = LEFT;
        mario->Y = 1;
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
        // mario ubrzav/trci
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


    bool X = false;
    bool Y = false;
    for(const std::shared_ptr<Object>& el : *objects) // provjerava za sve objekte da li ce se mario sudariti sa nima ukoliko se pomjeri za dx, dy
    {
        if(el->checkX(mario, dx)) // ako ce se sudariti sa nekim govorimo pozivaocu da ne mozemo odraditi pomjeranje
        {
            X = true;
        }
        if(el->checkY(mario, dy))
        {
            Y = true;
        }
        if(X && Y)
            break;
    }

    if(!X)
    {
//        std::cout << "UpdatePositionOfObjects dx: " << dx << std::endl;
        background->x += dx;
    }
    if(!Y)
    {
//        std::cout << "UpdatePositionOfObjects dy: " << dy << std::endl;
        background->y += dy;
    }


    for(const auto& el : *objects)
    {
        if(!X)
        {
            el->x -= dx;
            el->startingX -= dx;
        }
        if(!Y)
        {
            el->y -= dy;
            el->startingY -= dy;
        }
    }
    if(X && Y)
        return false;

    return true;
}

void Game::GenerateObjects()
{
    std::shared_ptr<Object> objPtr = nullptr;
    objects->push_back(std::make_shared<QuestionBlock>(objects, movingObjects, 176, 201));
    objects->push_back(std::make_shared<QuestionBlock>(objects, movingObjects, 193, 201));
    objects->push_back(std::make_shared<QuestionBlock>(objects, movingObjects, 224, 153));
    objects->push_back(std::make_shared<QuestionBlock>(objects, movingObjects, 240, 153));
    objects->push_back(std::make_shared<QuestionBlock>(objects, movingObjects, 416, 169));
    objects->push_back(std::make_shared<QuestionBlock>(objects, movingObjects, 120, 201));
    objPtr = std::make_shared<Pipe>(335, 240, objects, movingObjects);
    objects->push_back(objPtr);
    objects->push_back(std::make_shared<Ground>(25, 200));
    objPtr = std::make_shared<Ground>(0, 264);
    objPtr->rightSide = 500;
    objPtr->leftSide = 0;
    objPtr->hbm_ = nullptr;
    std::cout << "ground topSide: " << objPtr->y + objPtr->topSide << std::endl;
    objects->push_back(objPtr);

    objects->push_back(std::make_shared<FlowerEnemy>(objects, movingObjects, 359, 221, (TIMERPROC)&PiranhaTimerUp, (TIMERPROC)&PiranhaTimerDown));
}

