#include "../include/QuestionBlock.hpp"
#include "../include/Coin.hpp"

QuestionBlock::QuestionBlock(int x, int y)
{
//    this->objects = obj;
//    this->movingObjects = movingObj;
    this->typeOfObject = objectType::QuestionBlock;
    this->x = x;
    this->startingY = this->y = y;
    this->dy_ = 0;
    this->hbm_ = hbmQuestionMark_;
    this->hbmMask_ = hbmQuestionMarkMask_;
    GetObject(this->hbm_, sizeof(BITMAP), &bitmap);
    this->width = bitmap.bmWidth/4;
    this->height = bitmap.bmHeight;
    this->maxCycles_ = 4;
    this->X_ = 0;
    this->leftSide = 0;
    this->rightSide = 14;
    this->topSide = 0;
    this->bottomSide = 16;
    this->cyclesForChange = 3;
}

bool QuestionBlock::checkBottom(std::shared_ptr<Object> obj, int dy_)
{
//    static bool hit = false;
    if(checkYBottom(obj) && checkXRange(obj) && (dy_ < 0))
    {
//        hit = true;
        obj->stY_ = stateY::Down;
        obj->dy_ = (obj->testingY - obj->y + 1);
//                std::cout << "obj->dy_: " << obj->dy_ << std::endl;
//                std::cout << "-------------------------------------------------------------\n";
//                std::cout << "hit question mark\n";
//                std::cout << "-------------------------------------------------------------\n";
        if(!this->flag)
        {
//                    std::cout << "-------------------------------------------------------------\n";
//                    std::cout << "hit full question mark\n";
//                    std::cout << "-------------------------------------------------------------\n";
            this->dy_ = -8;
            this->flag = true;
//                    this->startingY = this->y;
            this->hbm_ = hbmEmptyQuestionMark_;
            this->hbmMask_ = hbmEmptyQuestionMarkMask_;
            this->maxCycles_ = 1;
            objects->push_back(std::make_shared<Coin>(this->x, this->y, true));
        }
//                std::cout << "-------------------------------------------------------------\n";
//                std::cout << "obj->y-obj->dy_: " << obj->y-obj->dy_ << "\ntestMarioY: " << obj->testingY << std::endl;
//                std::cout << "-------------------------------------------------------------\n";
//            praviUpdate(hwnd);
//            Render(hwnd);

//            obj->dy_ = -12;
        return true;
    }
//    else if(hit)
//    {
////        hit = false;
////        obj->dy_ = 12;
//        return true;
//    }
    return false;
}

bool QuestionBlock::checkTop(std::shared_ptr<Object> obj, int dy_)
{
    if(checkYTop(obj) && checkXRange(obj) && (obj->dy_ >= 0))
    {
//        std::cout << getStringTypeOfObject(obj) << " hit QuestionBlock top\n";
        obj->setYState(stateY::Neutral);
//        obj->stY_ = stateY::Neutral;
        obj->dy_ = obj->testingY - obj->y;
        obj->ground = obj->testingY + obj->bottomSide;
//        obj->objectY = 1;
        return true;
    }
    return false;
}

bool QuestionBlock::checkLeft(std::shared_ptr<Object> obj, int dx_)
{
    if(checkYRange(obj) && checkXLeft(obj) && (obj->dx_ > 0))
    {
        std::cout << "----------------------------------\n";
        std::cout << Object::getStringTypeOfObject(obj) << " hit left side of questionmark\n";
        std::cout << "----------------------------------\n";
        return true;
    }
    return false;
}

bool QuestionBlock::checkRight(std::shared_ptr<Object> obj, int dx_)
{
    if(checkYRange(obj) && checkXRight(obj) && (obj->dx_ < 0))
    {
        std::cout << "----------------------------------\n";
        std::cout << Object::getStringTypeOfObject(obj) << " hit right side of questionmark\n";
        std::cout << "----------------------------------\n";
        return true;
    }
    return false;
}

void QuestionBlock::moveYX()
{
    if((this->y < this->startingY) && (this->flag))
    {
//            std::cout << this->dy_ << std::endl;
        this->dy_ += 3;
        if((this->y + this->dy_) >= this->startingY)
        {
            this->dy_ = 0;
            this->y = this->startingY;
        }
    }
    this->moveY();
    this->moveX();
}

void QuestionBlock::moveY()
{
    this->y += this->dy_;
}

void QuestionBlock::moveX()
{
    this->x += this->dx_;
}

const std::string QuestionBlock::getStringTypeOfObject() const
{
    return std::string("QuestionBlock");
}
