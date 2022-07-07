#include "QuestionBlock.hpp"
#include "Coin.hpp"

QuestionBlock::QuestionBlock(vektorObjekata obj, vektorObjekata movingObj, int x, int y)
{
    this->objects = obj;
    this->movingObjects = movingObj;
    this->typeOfObject = QUESTIONMARK;
    this->x = x;
    this->startingY = this->y = y;
    this->dy = 0;
    this->hbm_ = questionMark;
    this->hbmMask_ = questionMarkMask;
    GetObject(this->hbm_, sizeof(BITMAP), &bitmap);
    this->width = bitmap.bmWidth/4;
    this->height = bitmap.bmHeight;
    this->max = 4;
    this->X = 0;
    this->leftSide = 0;
    this->rightSide = 14;
    this->topSide = 0;
    this->bottomSide = 16;
    this->cyclesForChange = 3;
}

bool QuestionBlock::checkBottom(std::shared_ptr<Object> obj, int dy)
{
    static bool hit = false;
    if(checkYBottom(obj) && checkXRange(obj))
    {
        hit = true;
        obj->stateY = DOWN;
        obj->dy = (obj->testingY - obj->y + 1);
//                std::cout << "obj->dy: " << obj->dy << std::endl;
//                std::cout << "-------------------------------------------------------------\n";
//                std::cout << "hit question mark\n";
//                std::cout << "-------------------------------------------------------------\n";
        if(!this->flag)
        {
//                    std::cout << "-------------------------------------------------------------\n";
//                    std::cout << "hit full question mark\n";
//                    std::cout << "-------------------------------------------------------------\n";
            this->dy = -8;
            this->flag = true;
//                    this->startingY = this->y;
            this->hbm_ = emptyQuestionMark;
            this->hbmMask_ = emptyQuestionMarkMask;
            this->max = 1;
            objects->push_back(std::make_shared<Coin>(this->objects, this->movingObjects, this->x, this->y, true));
        }
//                std::cout << "-------------------------------------------------------------\n";
//                std::cout << "obj->y-obj->dy: " << obj->y-obj->dy << "\ntestMarioY: " << obj->testingY << std::endl;
//                std::cout << "-------------------------------------------------------------\n";
//            praviUpdate(hwnd);
//            Render(hwnd);

//            obj->dy = -12;
        return true;
    }
//    else if(hit)
//    {
////        hit = false;
////        obj->dy = 12;
//        return true;
//    }
    return false;
}

bool QuestionBlock::checkTop(std::shared_ptr<Object> obj, int dy)
{
    if(checkYTop(obj) && checkXRange(obj) && (obj->dy >= 0))
    {
//        std::cout << getStringTypeOfObject(obj) << " hit QuestionBlock top\n";
        obj->stateY = NEUTRAL;
        obj->dy = obj->testingY - obj->y;
        obj->ground = obj->testingY + obj->bottomSide;
        obj->objectY = 1;
        return true;
    }
    return false;
}

bool QuestionBlock::checkLeft(std::shared_ptr<Object> obj)
{
    if(((obj->x + obj->rightSide) == (this->x + this->leftSide)) && ((((obj->y + obj->bottomSide) <= (this->y + this->bottomSide)) && ((obj->y + obj->bottomSide) > (this->y + this->topSide))) || (((obj->y + obj->topSide) <= (this->y + this->bottomSide)) && ((obj->y + obj->topSide) > (this->y + this->topSide)))))
    {
        std::cout << "----------------------------------\n";
        std::cout << getStringTypeOfObject(obj) << " hit left side of questionmark\n";
        std::cout << "----------------------------------\n";
        return true;
    }
    return false;
}

bool QuestionBlock::checkRight(std::shared_ptr<Object> obj)
{
    if(((obj->x + obj->leftSide) == (this->x + this->rightSide)) && (((obj->y + obj->bottomSide) < (this->y + this->bottomSide)) && ((obj->y + obj->bottomSide) > (this->y + this->topSide)) || ((obj->y + obj->topSide) <= (this->y + this->bottomSide)) && ((obj->y + obj->topSide) > (this->y + this->topSide))))
    {
        std::cout << "----------------------------------\n";
        std::cout << getStringTypeOfObject(obj) << " hit right side of questionmark\n";
        std::cout << "----------------------------------\n";
        return true;
    }
    return false;
}

void QuestionBlock::moveYX(std::shared_ptr<Object> obj, bool whosMoving)
{
    if((this->y < this->startingY) && (this->flag))
    {
//            std::cout << this->dy << std::endl;
        this->dy += 3;
        if((this->y + this->dy) >= this->startingY)
        {
            this->dy = 0;
            this->y = this->startingY;
        }
    }
    this->moveY(obj, whosMoving);
    this->moveX(obj, whosMoving);
}

void QuestionBlock::moveY(std::shared_ptr<Object> obj, bool whosMoving)
{
    this->y += this->dy;
}

void QuestionBlock::moveX(std::shared_ptr<Object> obj, bool whosMoving)
{
    this->x += this->dx;
}
