#include "../include/Game.hpp"

Game::Game()
{
//    movingObjects->push_back(mario);
    objects->push_back(mario);
    // dodaj samo goombe u movingObjects?
    Object::mario = mario;
    Object::objects = objects;
    Object::newObjects = newObjects;
    GenerateObjects();
}

void Game::CheckInput(void)
{
//    std::cout << "mario->dx_: " << mario->dx_ << " mario->y: " << mario->y << std::endl;



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
//        mario->dy_ = -22;
//        if(mario->y <= (VISINAPROZORA/2-mario->height/2 - 10) && ((initial_ground.y - background->y + 211) >= VISINAPROZORA))
//        {
//            std::cout << "camera jumped up\n";
//            ground.y += mario->dy_;
//            initial_ground.y += mario->dy_;
//            UpdatePositionOfObjects(0, mario->dy_);
//        }
//        else if(mario->y + mario->height/2  >= VISINAPROZORA/2 - 10)
//        {
//            std::cout << "mario jumped up\n";
//            mario->y -= mario->dy_;
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
            UpdatePositionOfObjects(mario->dx_, 0);
//            uint16_t totaldx_ = 0;
//            uint16_t testdx_ = 1;
//            std::cout << "pokusava se kretati desno ali " << mario->dx_ << std::endl;
//            while(totaldx_ != mario->dx_)
//            {
//                if(UpdatePositionOfObjects(testdx_, 0))
//                    mario->startingX += - testdx_; // more like mario->startingdx_
//                else
//                    break;
//                totaldx_ += testdx_;
//            }
        }
        else if(mario->x + mario->rightSide < SIRINAPROZORA) // kad ode skroz na desno
        {
            mario->x += mario->dx_;
//            uint16_t totaldx_ = 0;
//            uint16_t testdx_ = 1; // smoother walking("more precise")/updating
//            while(totaldx_ != mario->dx_)
//            {
//                if(mario->x + mario->rightSide + testdx_ < SIRINAPROZORA)
//                    mario->x += testdx_;
//                else
//                    break;
//                totaldx_ += testdx_;
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
//        (std::dy_namic_pointer_cast<Mario>(mario))->setWalkLeft();
//        mario->stX_ = Object::stateX::Left;
//        mario->Y = 1;
        if(background->x > 0 && (mario->centerX() <= (SIRINAPROZORA / 2)))
        {
//            mario->x = (SIRINAPROZORA / 2);
            UpdatePositionOfObjects(mario->dx_, 0);
//            int totaldx_ = 0;
//            int testdx_ = -1;
//            while(totaldx_ != mario->dx_)
//            {
//                if(UpdatePositionOfObjects(testdx_, 0))
//                    mario->startingX += -testdx_; // za koliko revertati u slucaju da treba da se reverta
//                else
//                    break;
//                totaldx_ += testdx_;
//            }
//            foreground.x -= mario->dx_;
        }
        else if(mario->x + mario->leftSide > 0)
        {
            mario->x += mario->dx_;
//            int totaldx_ = 0;
//            int testdx_ = -1;
//            while(totaldx_ != -mario->dx_)
//            {
//                if(mario->x + testdx_ + 10 > 0)
//                    mario->x += testdx_;
//                else
//                    break;
//                totaldx_ += testdx_;
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

void Game::UpdatePositionOfObjects(int dx_, int dy_) // relative to obj (for example Mario)
{
    background->x += dx_;
    background->y += dy_;

    mario->ground -= dy_;

    for(const auto& el : *objects)
    {
        if(el == mario)
            continue;
        el->x -= dx_;
        el->startingX -= dx_;
        el->y -= dy_;
        el->startingY -= dy_;
    }

//    bool X = false;
//    bool Y = false;
//    for(const std::shared_ptr<Object>& el : *objects) // provjerava za sve objekte da li ce se mario sudariti sa nima ukoliko se pomjeri za dx_, dy_
//    {
//        if(el->checkX(mario, dx_)) // ako ce se sudariti sa nekim govorimo pozivaocu da ne mozemo odraditi pomjeranje
//        {
//            std::cout << "Mario se sudara po x-u\n";
//            X = true;
//        }
//        if(el->checkY(mario, dy_))
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
////        std::cout << "UpdatePositionOfObjects dx_: " << dx_ << std::endl;
//        background->x += dx_;
//    }
//    if(!Y)
//    {
////        std::cout << "UpdatePositionOfObjects dy_: " << dy_ << std::endl;
//        background->y += dy_;
//    }
//
//
//    for(const auto& el : *objects)
//    {
//        if(!X)
//        {
//            el->x -= dx_;
//            el->startingX -= dx_;
//        }
//        if(!Y)
//        {
//            el->y -= dy_;
//            el->startingY -= dy_;
//        }
//    }
//    if(X && Y)
//        return false;
//
//    return true;
}

void Game::GenerateObjects()
{
    const std::string configPath = "config.ini";
    generateObjects(configPath);
//    std::shared_ptr<Object> objPtr = nullptr;
//    objects->push_back(std::make_shared<QuestionBlock>(176, 201));
//    objects->push_back(std::make_shared<QuestionBlock>(193, 201));
//    objects->push_back(std::make_shared<QuestionBlock>(224, 153));
//    objects->push_back(std::make_shared<QuestionBlock>(240, 153));
//    objects->push_back(std::make_shared<QuestionBlock>(416, 169));
//    objects->push_back(std::make_shared<QuestionBlock>(120, 201));
//    objPtr = std::make_shared<Pipe>(335, 240);
//    objects->push_back(std::make_shared<FlowerEnemy>(359, 221, objPtr, FlowerEnemy::flowerType::thrower));
//    objects->push_back(objPtr);
//    objects->push_back(std::make_shared<Ground>(25, 200));
//
//    objPtr = std::make_shared<Ground>(0, 264);
//    objPtr->rightSide = 600;
//    objPtr->leftSide = 0;
//    objPtr->hbm_ = objPtr->hbmMask_ = nullptr;
//    objects->push_back(objPtr);
//
//    objPtr = std::make_shared<Ground>(272, 185, true);
//    objPtr->rightSide = 47;
//    objPtr->leftSide = 0;
//    objPtr->hbm_ = objPtr->hbmMask_ = nullptr;
//    objects->push_back(objPtr);
//
//    objPtr = std::make_shared<Ground>(240, 215, true);
//    objPtr->rightSide = 47;
//    objPtr->leftSide = 0;
//    objPtr->hbm_ = objPtr->hbmMask_ = nullptr;
//    objects->push_back(objPtr);

//    objects->push_back(std::make_shared<Turtle>(245, 170));

//    objects->push_back(std::make_shared<FlowerEnemy>(objects, movingObjects, 359, 221, (TIMERPROC)&PiranhaTimerUp, (TIMERPROC)&PiranhaTimerDown));

//    objects->push_back(std::make_shared<Goomba>(300, 250));
//    objects->push_back(std::make_shared<Turtle>(40, 235));
//    objects->push_back(std::make_shared<Fireball>(mario->x, mario->y, -1, -1));
}

void Game::generateObjects(const std::string& configFile)
{
    std::ifstream input(configFile);
    std::string line;
    std::vector<ObjectArgs> objectArgs;

    // Read the configuration file line by line
    while (std::getline(input, line))
    {
        // Skip comments and empty lines
        if (line.empty() || line[0] == '#')
        {
            continue;
        }

        // Parse the line into object type and arguments
        std::istringstream iss(line);
        std::string type;
        std::string arg;
        std::vector<std::string> args;

        iss >> type;
        if(type.back() == ',') type.pop_back();
        while (iss >> arg)
        {
            if(arg.back() == ',') arg.pop_back();
            args.push_back(arg);
        }

        // Store the object type and arguments
        objectArgs.push_back({type, args});
    }

    // Generate objects from the parsed arguments
    for (const auto& object : objectArgs)
    {
        std::shared_ptr<Object> objPtr = nullptr;
        int x = std::stoi(object.args[0]);
        int y = std::stoi(object.args[1]);

        if (object.type == "question_block")
        {
            objects->push_back(std::make_shared<QuestionBlock>(x, y));
        }
        else if (object.type == "pipe")
        {
            objects->push_back(std::make_shared<Pipe>(x, y));
        }
        else if (object.type == "flower_enemy")
        {
            FlowerEnemy::flowerType type;
            if(object.args[2] == "thrower") type = FlowerEnemy::flowerType::thrower;
            else if(object.args[2] == "eater") type = FlowerEnemy::flowerType::eater;
            objects->push_back(std::make_shared<FlowerEnemy>(x, y, objects->back(), type));
        }
        else if (object.type == "ground")
        {
            objPtr = std::make_shared<Ground>(x, y);
            for(const auto& el : object.args) {
                    std::cout << el << std::endl;
            }
            if(object.args.size() > 2)
            {
                if(object.args[2] == "true") objPtr = std::make_shared<Ground>(x, y, true);
                else if(object.args[2] == "false") objPtr = std::make_shared<Ground>(x, y, false);
                else std::cerr << "Error while parsing ground" << std::endl;
            }
            if(object.args.size() > 3)
            {
                objPtr->leftSide = std::stoi(object.args[3]);
            }
            if(object.args.size() > 4)
            {
                objPtr->rightSide = std::stoi(object.args[4]);
            }
            if(object.args.size() > 5)
            {
                objPtr->topSide = std::stoi(object.args[5]);
            }
            if(object.args.size() > 6)
            {
                objPtr->bottomSide = std::stoi(object.args[6]);
            }
            if(object.args.size() > 7)
            {
                if(object.args[7] == "true") objPtr->hbm_ = objPtr->hbmMask_ = nullptr;;
            }
            if(object.args.size() > 8)
            {
                std::cerr << "Too many arguments while parsing ground" << std::endl;
            }
            objects->push_back(objPtr);
        }
        else if(object.type == "goomba")
        {
            objects->push_back(std::make_shared<Goomba>(x, y));
        }
        else if(object.type == "turtle")
        {
            objects->push_back(std::make_shared<Turtle>(x, y));
        }
        else
        {
            std::cerr << "Unrecognized object name: " << object.type << std::endl;
        }
    }
}

