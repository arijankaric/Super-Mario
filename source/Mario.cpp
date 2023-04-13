#include "Mario.hpp"

Mario::Mario(int x, int y)
{
    this->Y = 0;
    this->cyclesForChange = 3;
    this->max = 2;
//    this->objects = obj;
//    this->movingObjects = movObj;
    this->hbm_ = hbmMarioWalkRight;
    this->hbmMask_ = hbmMarioWalkRightMask;
    GetObject(hbm_, sizeof(BITMAP), &bitmap);
    this->typeOfObject = objectType::Mario;
    this->width = bitmap.bmWidth/3;
    this->height = bitmap.bmHeight/10;
    this->y = 239;
    this->x = SIRINAPROZORA/2-this->width/2;
    this->dx = 0;
    this->dy = 0;
    this->bottomSide = 25;
    this->leftSide = 12;
    this->rightSide = 24;
    this->topSide = 10;
    this->ground = 320;
    this->life_ = 1;
    this->moveable = true;
}

//bool Mario::checkLeft(std::shared_ptr<Object> obj)
//{
//    if(checkXLeft(obj) && checkYRange(obj))
//    {
//        std::cout << "left side " << getStringTypeOfObject(this) << " collided with " << getStringTypeOfObject(obj) << std::endl;
//        return false;
//    }
//    return true;
//}
//
//bool Mario::checkRight(std::shared_ptr<Object> obj)
//{
//    if(checkXRight(obj) && checkYRange(obj))
//    {
//        std::cout << "right side " << getStringTypeOfObject(this) << " collided with " << getStringTypeOfObject(obj) << std::endl;
//        return false;
//    }
//    return true;
//}
//
//bool Mario::checkTop(std::shared_ptr<Object> obj)
//{
//    if(checkYTop(obj) && checkXRange(obj))
//    {
//        std::cout << "top side " << getStringTypeOfObject(this) << " collided with " << getStringTypeOfObject(obj) << std::endl;
//        return false;
//    }
//    return true;
//}
//
//bool Mario::checkBottom(std::shared_ptr<Object> obj)
//{
//    if(checkYBottom(obj) && checkXRange(obj))
//    {
//        std::cout << "bottom side " << getStringTypeOfObject(this) << " collided with " << getStringTypeOfObject(obj) << std::endl;
//        return false;
//    }
//    return true;
//}

void Mario::setWalkLeft()
{
    this->hbm_ = this->hbmMarioWalkLeft;
    this->hbmMask_ = this->hbmMarioWalkLeftMask;
}

void Mario::setWalkRight()
{
    this->hbm_ = this->hbmMarioWalkRight;
    this->hbmMask_ = this->hbmMarioWalkRightMask;
}

void Mario::setYState(stateY st)
{
    static bool hit = false;
    if(stateY::Neutral == st)
    {
        hit = false;
        if(stX_ == stateX::Neutral)
        {
            Y = 0;
            max = 1;
        }
    }
    else if(st == stateY::Up)
    {
        if(stY_ == stateY::Neutral)
        {
            std::cout << "inicijalni skok\n";
            dy = -16;
        }
        else
        {
            if((dy < 0) && (dy > -8) && !hit)
            {
                hit = true;
                std::cout << "sekundarni skok: " << y + bottomSide << " " << ground << std::endl;
                dy -= 10;
            }
            return;
        }
        Y = 3;
        X = 0;
        max = 1;
    }
    else // Down je isto kao i up?
    {

    }
    Object::setYState(st);
}

void Mario::setXState(stateX st)
{
    Object::setXState(st);

    if(stateX::Left == st)
    {
        Y = 1;
        max = 2;
        dx = -5;
        setWalkLeft();
    }
    else if(stateX::Right == st)
    {
        Y = 1;
        max = 2;
        dx = 5;
        setWalkRight();
    }
    else // Neutral
    {
        Y = 0;
        max = 1;
        // setNeutral();?
    }
}

void Mario::nextDY(void)
{
    this->dy += 3;
}
//
//void Mario::nextY(void)
//{
////    this->moveY();?
//}

//void Mario::changeY(int dy)
//{
//    if()
//}

void Mario::decreaseLife()
{
    std::cout << "Mario lifes before: " << life_ << std::endl;
    if(--life_ == 0)
    {
        this->X = 0;
        this->Y = 0;
        this->max = 1;
        hbm_ = hbmMarioDead_;
        hbmMask_ = hbmMarioDeadMask_;
        GetObject(hbm_, sizeof(BITMAP), &bitmap);
        this->width = bitmap.bmWidth;
        this->height = bitmap.bmHeight;
        this->x += 10;
//        this->y -= 3;
        this->dy = -14;
        this->leftSide -= 13;
        this->rightSide -= 8;
        this->bottomSide -= 9;
        this->topSide -= 11;
        this->cyclesUntilDeath = -2;
    }
    std::cout << "Mario lifes after: " << life_ << std::endl;
}

void Mario::decreaseMarioState(void)
{
    if(st_ == marioState::small)
    {
        decreaseLife();
    }
    else if(st_ == marioState::super)
    {
        st_ = marioState::small;
    }
    else if(st_ == marioState::raccoon)
    {
        st_ = marioState::super;
    }
}

void Mario::setMarioState(marioState st)
{
    if(st ==  marioState::super)
    {
        st_ = st;
    }
    else if(st == marioState::raccoon)
    {
        st_ = st;
    }
    else if(st == marioState::sparkling)
    {
        st_ = st;
    }
}

const std::string Mario::getStringTypeOfObject() const
{
    return std::string("Mario");
}

void Mario::collideX(std::shared_ptr<Object> obj)
{
    if(deadly(obj))
        decreaseMarioState();
}

const bool Mario::deadly(const std::shared_ptr<Object> obj) const
{
    switch(obj->typeOfObject)
    {
    case objectType::Goomba:
        return true;
        break;
    case objectType::Turtle:
        return true;
        break;
    case objectType::Fireball:
        return true;
        break;
    case objectType::FlowerEnemy:
        return true;
        break;
    default:
        return false;
    }
}

void Mario::projectY()
{
    if(life_ != 0)
    {
        Object::projectY();
        return;
    }

//    if(this->cycles == (5))
//    {
//        std::cout << "Mario has changed direction, even in his death Mario remains agile. AGILE ENVIRONMENTS FTW!! : D\n";
//        this->dy = -this->dy;
//    }


    if(this->cyclesUntilDeath != -1)
    {
        ++this->cycles;
//        std::cout << "Only dying Mario should print this: " << this->cycles << std::endl;
    }

//    std::cout << "marioTop: " << this->getTop() << std::endl;
//    std::cout << "VISINAPROZORA: " << VISINAPROZORA << std::endl;

    if(this->getTop() > VISINAPROZORA)
    {
//        this->removeDeadObject(shared_from_this());
    }
}

