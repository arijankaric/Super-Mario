#include "../include/distanceBetweenObjects.hpp"

bool Object::checkX(std::shared_ptr<Object> obj, int dx_) // checkXFuture, napravi checkXCurrent(bez int dx_)
{
    return ((checkLeft(obj, dx_)) || (checkRight(obj, dx_)));
}

bool Object::checkY(std::shared_ptr<Object> obj, int dy_) // checkYFuture, napravi checkYCurrent(bez int dy_)
{
    return ((checkTop(obj, dy_)) || (checkBottom(obj, dy_)));
}

Object::~Object()
{
    std::cout << "Object destructor: " << getStringTypeOfObject(this) << " x: " << x << " y: " << y << std::endl;
}

void Object::projectX()
{
    //            std::cout << getStringTypeOfObject(this) << " is moving on X " << whosMoving << std::endl;
    int endPointX = this->x + this->dx_;
    int directionX;
    if(this->dx_ == 0)
    {
        return;
        directionX = 0;
    }
    else
        directionX = this->dx_/abs(this->dx_);
    for(const auto& objTest : *objects)
    {
//            if(distanceBetweenObjects(this, objTest.get()) > 100)
//                continue;

        if(objTest == shared_from_this())
        {
            continue;
        }

        this->testingX = this->x;

        while(this->testingX != endPointX)
        {
//            if(this->typeOfObject == objectType::Mario)
//            {
//                std::cout << "turtle->this->testingX: " << this->testingX << std::endl;
//            }
            if(objTest->checkRight(shared_from_this(), directionX))
            {
                break;
            }
            else if(objTest->checkLeft(shared_from_this(), directionX))
            {
                break;
            }
            this->testingX += directionX;
        }
//        if(this->typeOfObject == objectType::Mario)
//            std::cout << "this->testingX: " << this->testingX << std::endl;
        if(((this->testingX < endPointX) && (directionX > 0)) || ((this->testingX > endPointX) && (directionX < 0)))
        {
//            std::cout << "shorted/cut\n";
            endPointX = this->testingX;
        }
        if(collidedx_ && (this->typeOfObject != objectType::Mario))
        {
//            std::cout << "collided in projectX\n";
            endPointX = this->x + this->dx_;

//            this->dx_ = (endPointX - this->x);
            collidedx_ = false;

            if(this->dx_ == 0)
            {
                return;
                directionX = 0;
            }
            else
                directionX = this->dx_/abs(this->dx_);
//            std::cout << "endPointX: " << endPointX << " dx_: " << this->dx_ << " testingX: " << this->testingX << " directionX: " << directionX << std::endl;
//            system("pause");
        }
    }
    this->dx_ = (endPointX - this->x);
}

void Object::moveX()
{
    projectX();
    x += dx_;
//    std::cout << this->x << " " << getStringTypeOfObject(shared_from_this()) << std::endl;
//    this->testingX = this->x;
//    int directionX;
//    if(this->dx_ == 0)
//        directionX = 0;
//    else
//        directionX = this->dx_/abs(this->dx_);
//    int endPoint = this->x + this->dx_;
//    while(this->testingX != endPoint)
//    {
//        if(checkLeft(obj, directionX))
//            break;
//        else if(checkRight(obj, directionX))
//            break;
//        this->testingX += directionX;
//    }
//    this->x += this->dx_;
}

void Object::projectY()
{
    //        std::cout << getStringTypeOfObject(this) << " is moving on Y " << whosMoving << std::endl;

    int directionY;
    if(this->dy_ == 0)
    {
        return;
        directionY = 0;
    }
    else
        directionY = this->dy_/abs(this->dy_);

    int endPointY = this->y + this->dy_;
    for(const auto& objTest : *objects)
    {
//            if(distanceBetweenObjects(this, objTest.get()) > 100)
//                continue;
        if(objTest == shared_from_this())
        {
            continue;
        }

        this->testingY = this->y;

        while(this->testingY != endPointY)
        {
//            std::cout << "Prije: " << testingY << std::endl;
            if(testingY < 0)
            {
//                std::cout << "testingY < 0\n";
//                std::cout << "this->y: " << this->y << std::endl;
//                std::cout << "this->dy_: " << this->dy_ << std::endl;
//                std::cout << this->getStringTypeOfObject() << std::endl;
//                system("pause");
            }
            if(objTest->checkBottom(shared_from_this(), directionY))
            {
                break;
            }
            else if(objTest->checkTop(shared_from_this(), directionY))
            {
                break;
            }
            this->testingY += directionY;
        }
        if(((this->testingY < endPointY) && directionY > 0) || ((this->testingY > endPointY) && directionY < 0))
        {
            endPointY = this->testingY;
        }
    }
    this->dy_ = (endPointY - this->y);
//        this->y += this->dy_;
}

void Object::moveY() // limits dy_, so it doesn't go too far
{
    projectY();
    y += dy_;
//    std::cout << getStringTypeOfObject(obj) << " is moving on Y " << whosMoving << std::endl;
//    this->testingY = this->y;
//    int directionY;
//    if(this->dy_ == 0)
//        directionY = 0;
//    else
//        directionY = this->dy_/abs(this->dy_);
//    int endPoint = this->y + this->dy_;
//    while(this->testingY != endPoint)
//    {
//        if(checkBottom(obj, directionY))
//            break;
//        else if(checkTop(obj, directionY))
//            break;
//        this->testingY += directionY;
//    }
//    this->y += this->dy_;
}

const std::string Object::getStringTypeOfObject(Object* objPtr)
{
    if(objPtr == nullptr)
    {
        return std::string("nullptr");
    }
    switch(objPtr->typeOfObject)
    {
    case objectType::Pipe:
        return std::string("PIPE");
    case objectType::Goomba:
        return std::string("GOOMBA");
    case objectType::QuestionBlock:
        return std::string("QUESTIONMARK");
    case objectType::FlowerEnemy:
        return std::string("FLOWER_ENEMY");
    case objectType::Coin:
        return std::string("COIN");
    case objectType::Mario:
        return std::string("MARIO");
    case objectType::Ground:
        return std::string("GROUND");
    case objectType::Turtle:
        return std::string("TURTLE");
    case objectType::Fireball:
        return std::string("FIREBALL");
    default:
        return std::string("unidentified object");
    }
}

const std::string Object::getStringTypeOfObject(std::shared_ptr<Object> obj)
{
    if(obj == nullptr)
    {
        return std::string("nullptr");
    }
    switch(obj->typeOfObject)
    {
    case objectType::Pipe:
        return std::string("PIPE");
    case objectType::Goomba:
        return std::string("GOOMBA");
    case objectType::QuestionBlock:
        return std::string("QUESTIONMARK");
    case objectType::FlowerEnemy:
        return std::string("FLOWER_ENEMY");
    case objectType::Coin:
        return std::string("COIN");
    case objectType::Mario:
        return std::string("MARIO");
    case objectType::Ground:
        return std::string("GROUND");
    case objectType::Turtle:
        return std::string("TURTLE");
    case objectType::Fireball:
        return std::string("FIREBALL");
    default:
        return std::string("unidentified object");
    }
}

void Object::draw(HDC hdcBuffer, HDC hdcMem)
{
//    if(this->typeOfObject == objectType::Turtle && this->life_ == 1)
//    {
//        this->Y_ = 1;
//        std::cout << "turtle->Y: " << this->Y_ << std::endl;
//    }

    SelectObject(hdcMem, hbm_);
    BitBlt(hdcBuffer, this->x, this->y, this->width, this->height, hdcMem, this->X_ * this->width, this->Y_ * this->height, SRCAND);

    SelectObject(hdcMem, hbmMask_);
    BitBlt(hdcBuffer, this->x, this->y, this->width, this->height, hdcMem, this->X_ * this->width, this->Y_ * this->height, SRCPAINT);

}

bool Object::checkXRange(std::shared_ptr<Object> obj) const
{
    if((((this->x + this->leftSide) < (obj->x + obj->rightSide)) && ((this->x + this->rightSide) > (obj->x + obj->leftSide))))
        return true;
    return false;
}

bool Object::checkYRange(std::shared_ptr<Object> obj) const
{
    if(((this->y + this->bottomSide) > (obj->y + obj->topSide)) && ((this->y + this->topSide) < (obj->y + obj->bottomSide)))
        return true;
    return false;
}

bool Object::checkXLeft(std::shared_ptr<Object> obj) const
{
    if((this->x + this->leftSide) == (obj->testingX + obj->rightSide))
        return true;
    return false;
}

bool Object::checkXRight(std::shared_ptr<Object> obj) const
{
    if((this->x + this->rightSide) == (obj->testingX + obj->leftSide))
        return true;
    return false;
}

bool Object::checkYTop(std::shared_ptr<Object> obj) const
{
    if((this->y + this->topSide) == (obj->testingY + obj->bottomSide))
        return true;
    return false;

}

bool Object::checkYBottom(std::shared_ptr<Object> obj) const
{
    if((this->y + this->bottomSide) == (obj->testingY + obj->topSide))
        return true;
    return false;
}

bool Object::checkLeft(std::shared_ptr<Object> obj, int dx_)
{
    if(checkXLeft(obj) && checkYRange(obj) && (obj->dx_ > 0))
    {
        std::cout << "left side " << getStringTypeOfObject(this) << " collided with " << getStringTypeOfObject(obj) << std::endl;
//        obj->collideX(shared_from_this());

        if(this->typeOfObject == objectType::Mario)
        {
            this->collideX(obj);
        }
        else
        {
            obj->collideX(shared_from_this());
            this->collideX(obj);
        }
        return true;
    }
    return false;
}

bool Object::checkRight(std::shared_ptr<Object> obj, int dx_)
{
//    if((this->typeOfObject == objectType::Mario) && (obj->typeOfObject == objectType::Goomba))
//    {
//        std::cout << this->x + this->rightSide << " " << obj->testingX + obj->leftSide << std::endl;
//        std::cout << checkXRight(obj) << " " << checkYRange(obj) << " " << dx_ << " " << obj->dx_ << std::endl;
//    }
    if(checkXRight(obj) && checkYRange(obj) && (obj->dx_ < 0))
    {
        std::cout << "right side " << getStringTypeOfObject(this) << " collided with " << getStringTypeOfObject(obj) << std::endl;
        if(this->typeOfObject == objectType::Mario)
        {
            this->collideX(obj);
        }
        else
        {
            obj->collideX(shared_from_this());
            this->collideX(obj);
        }
        return true;
    }
    return false;
}

bool Object::checkTop(std::shared_ptr<Object> obj, int dy_)
{
    if(checkYTop(obj) && checkXRange(obj) && (dy_ > 0))
    {
        std::cout << "topSide of " << getStringTypeOfObject(this) << " collided with bottomSide of " << getStringTypeOfObject(obj) << std::endl;
        return true;
    }
    return false;
}

bool Object::checkBottom(std::shared_ptr<Object> obj, int dy_)
{
    if(checkYBottom(obj) && checkXRange(obj) && (dy_ < 0))
    {
        std::cout << "bottomSide of " << getStringTypeOfObject(this) << " collided with topSide of " << getStringTypeOfObject(obj) << std::endl;
        return true;
    }
    return false;
}

void Object::moveYX()
{
//    if(distanceBetweenObjects(mario.get(), this) > VISINAPROZORA)
//    {
//        this->removeDeadObject(shared_from_this());
//        return;
//    }
    this->moveY();
    this->moveX();
}

void Object::setYState(stateY st)
{
    stY_ = st;
}
void Object::setXState(stateX st)
{
    stX_ = st;
}

void Object::nextdy_(void)
{
    // samo za goombe i maria za sada
}

void Object::setdx_(int dx_)
{

}

void Object::setdy_(int dy_)
{

}

void Object::collideX(std::shared_ptr<Object> obj)
{
//    std::cout << this->getStringTypeOfObject() << " collided with " << obj->getStringTypeOfObject() << std::endl;
    if(this->deadly(obj))
    {
        this->decreaseLife();
        return;
    }
    this->collidedx_ = true;
    this->dx_ = -this->dx_;
    return;
}

const bool Object::deadly(const std::shared_ptr<Object> obj) const // better function name isDeadly(...)
{
    if(this->typeOfObject != objectType::Mario)
    {
        return (obj->typeOfObject == objectType::Mario) || ((obj->typeOfObject == objectType::Turtle) && (obj->life_ == 1) && (obj->dx_ != 0));
    }
    else
    {
        return obj->typeOfObject != objectType::Mario;
    }
}


void Object::stompY(std::shared_ptr<Object> obj)
{
    if(this->deadly(obj))
    {
        this->decreaseLife();
    }
}

void Object::decreaseLife()
{

}

void Object::increaseLife()
{

}

//bool Object::checkEdge(std::shared_ptr<Object> obj) const
//{
//    if(checkLeftEdge(obj))
//    {
//        std::cout << "leftSide of " << getStringTypeOfObject(this) << " reached leftSide of " << getStringTypeOfObject(obj) << std::endl;
//        if(this->fall)
//        {
//            this->dx_ = - this->dx_;
//        }
//        return true;
//    }
//    else if(checkRightEdge(obj))
//    {
//        std::cout << "rightSide of " << getStringTypeOfObject(this) << " reached rightSide of " << getStringTypeOfObject(obj) << std::endl;
//        if(this->fall)
//        {
//            this->dx_ = - this->dx_;
//        }
//        return true;
//    }
//    return false;
//}

bool Object::checkLeftEdge(std::shared_ptr<Object> obj) const
{
//    if((this->typeOfObject == Object::objectType::Fireball) && (this->leftSide + this->x) == (obj->leftSide + obj->x) && (this->dx_ < 0))
//    {
//        std::cout << this->getStringTypeOfObject() << " y: " << this->y << std::endl;
//        std::cout << obj->getStringTypeOfObject() << " y: " << obj->y << std::endl;
//        system("pause");
//    }

    if(!((obj->typeOfObject == objectType::Ground) ||(this->typeOfObject == objectType::Ground))) // Can only hit edge of ground
        return false;

    return (this->leftSide + this->x) == (obj->leftSide + obj->x);
}

bool Object::checkRightEdge(std::shared_ptr<Object> obj) const
{
//    if((this->typeOfObject == Object::objectType::Fireball) && (this->rightSide + this->x) == (obj->rightSide + obj->x) && (this->dx_ > 0))
//    {
//        std::cout << this->getStringTypeOfObject() << " y: " << this->y << std::endl;
//        std::cout << obj->getStringTypeOfObject() << " y: " << obj->y << std::endl;
//        system("pause");
//    }

    if(((obj->typeOfObject == objectType::Turtle) || (this->typeOfObject == objectType::Turtle)) && ((obj->typeOfObject == objectType::Ground) ||(this->typeOfObject == objectType::Ground)))
    {
        std::cout << "this->getRight(): " << this->getRight() << "obj->getRight(): " << obj->getRight() << std::endl;
    }

    if(!((obj->typeOfObject == objectType::Ground) ||(this->typeOfObject == objectType::Ground))) // Can only hit edge of ground
        return false;

    return (this->rightSide + this->x) == (obj->rightSide + obj->x);
}

unsigned char Object::determineQuadrant() const
{
    if(this->getTop() > this->mario->centerY()) // upper quadrant 1,2
    {
        if(this->determineSide()) // upper right
        {
            return 1;
        }
        else // upper left
        {
            return 2;
        }
    }
    else // bottom quadrant 3,4
    {
        if(this->determineSide()) // bottom right
        {
            return 4;
        }
        else // bottom left
        {
            return 3;
        }
    }
}

bool Object::determineSide() const
{
    if(this->centerX() < this->mario->centerX()) // right
    {
        return true; // right side
    }
    else // left
    {
        return false;
    }
}

int Object::centerX() const
{
    return (getLeft() + getRight()) / 2;
}

int Object::centerY() const
{
    return (getBottom() + getTop()) / 2;
}

int Object::getBottom() const
{
    return this->y + this->bottomSide;
}

int Object::getTop() const
{
    return this->y + this->topSide;
}

int Object::getLeft() const
{
    return this->x + this->leftSide;
}

int Object::getRight() const
{
    return this->x + this->rightSide;
}

void Object::removeDeadObject(std::shared_ptr<Object> obj)
{
    std::cout << obj->getStringTypeOfObject() << " died at x: " << obj->x << " y: " << obj->y << std::endl;
    objects->erase(partition(std::begin(*objects), end(*objects),
                             [obj](const std::shared_ptr<Object> &x)
    {
        return (x.get() != obj.get());
    }),
    std::end(*objects));
    std::cout << "does removeDeadObject return?\n";
}

void Object::afterDraw()
{
    if(++this->changeCycles == this->cyclesForChange)
    {
        ++this->X_;
        this->changeCycles = 0;
    }

    if(this->X_ >= this->maxCycles_)
    {
        this->X_ = 0;
    }
}

bool Object::isSprite() const
{
    if((this->typeOfObject == objectType::Ground)
       || (this->typeOfObject == objectType::Pipe)) return false;
    return false;
}
