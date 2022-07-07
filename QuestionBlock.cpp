#include "QuestionBlock.hpp"
#include "Coin.hpp"

QuestionBlock::QuestionBlock(int x, int y)
{
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
}

bool QuestionBlock::checkBottom(std::shared_ptr<Object> obj)
{
    static bool hit = false;
    if((obj->stateY == UP) && ((obj->x + obj->leftSide) < (this->x + this->rightSide)) && ((obj->x + obj->rightSide) > (this->x + this->leftSide)) && ((obj->testingY + obj->topSide) == (this->y + this->bottomSide)) && (!hit))
    {
        hit = true;
        obj->stateY = DOWN;
        obj->dy = (obj->y - obj->testingY - 1);
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
            this->hbm_ = (HBITMAP) LoadImage(NULL, "emptyQuestionBlockBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            this->hbmMask_ = (HBITMAP) LoadImage(NULL, "emptyQuestionBlock.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            this->max = 1;

            objects->push_back(std::make_shared<Coin>(this->objects, this->movingObjects, this->x, this->y, true));
        }
//                std::cout << "-------------------------------------------------------------\n";
//                std::cout << "obj->y-obj->dy: " << obj->y-obj->dy << "\ntestMarioY: " << obj->testingY << std::endl;
//                std::cout << "-------------------------------------------------------------\n";
//            praviUpdate(hwnd);
//            Render(hwnd);

//            obj->dy = -12;
        return false;
    }
    else if(hit)
    {
        hit = false;
        obj->dy = -12;
        return false;
    }
    return true;
}

bool QuestionBlock::checkTop(std::shared_ptr<Object> obj)
{
    if((obj->stateY != UP) && ((obj->x + obj->leftSide) < (this->x + this->rightSide)) && ((obj->x + obj->rightSide) > (this->x + this->leftSide)) && ((obj->testingY + obj->bottomSide) == (this->y + this->topSide)))
    {
        std::cout << getStringTypeOfObject(obj) << " hit new(questionMark) ground\n";
        obj->stateY = NEUTRAL;
        obj->dy = obj->y - obj->testingY;
        obj->ground = obj->testingY;
        obj->objectY = 1;
        return false;
    }
    return true;
}

bool QuestionBlock::checkLeft(std::shared_ptr<Object> obj)
{
    if(((obj->x + obj->rightSide) == (this->x + this->leftSide)) && ((((obj->y + obj->bottomSide) <= (this->y + this->bottomSide)) && ((obj->y + obj->bottomSide) > (this->y + this->topSide))) || (((obj->y + obj->topSide) <= (this->y + this->bottomSide)) && ((obj->y + obj->topSide) > (this->y + this->topSide)))))
    {
        std::cout << "----------------------------------\n";
        std::cout << getStringTypeOfObject(obj) << " hit left side of questionmark\n";
        std::cout << "----------------------------------\n";
        return false;
    }
    return true;
}

bool QuestionBlock::checkRight(std::shared_ptr<Object> obj)
{
    if(((obj->x + obj->leftSide) == (this->x + this->rightSide)) && (((obj->y + obj->bottomSide) < (this->y + this->bottomSide)) && ((obj->y + obj->bottomSide) > (this->y + this->topSide)) || ((obj->y + obj->topSide) <= (this->y + this->bottomSide)) && ((obj->y + obj->topSide) > (this->y + this->topSide))))
    {
        std::cout << "----------------------------------\n";
        std::cout << getStringTypeOfObject(obj) << " hit right side of questionmark\n";
        std::cout << "----------------------------------\n";
        return false;
    }
    return true;
}
