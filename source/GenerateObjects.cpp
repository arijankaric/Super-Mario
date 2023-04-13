#include "GenerateObjects.hpp"
#include <iostream>

bool outline = true;

//void GenerateQuestionMark(int x, int y)
//{
//    BITMAP bitmap;
//    Object *newObj = new Object();
//    newObj->typeOfObject = QUESTIONMARK;
//    newObj->x = x;
//    newObj->startingY = newObj->y = y;
//    newObj->dy = 0;
//    newObj->hbm_ = questionMark;
//    newObj->hbmMask_ = questionMarkMask;
//    GetObject(newObj->hbm_, sizeof(BITMAP), &bitmap);
//    newObj->width = bitmap.bmWidth/4;
//    newObj->height = bitmap.bmHeight;
//    newObj->max = 4;
//    newObj->X = 0;
//    newObj->leftSide = 0;
//    newObj->rightSide = 14;
//    newObj->topSide = 0;
//    newObj->bottomSide = 16;
//    if(outline)
//        newObj->outline = true;
//    objects.push_back(newObj);
//}
//
//void* GeneratePipe(int x, int y)
//{
//    BITMAP bitmap;
//    Object *newObj = new Object();
//    newObj->typeOfObject = PIPE;
//    newObj->x = x;
//    newObj->startingY = newObj->y = y;
//    newObj->dy = 0;
//    newObj->hbm_ = NULL; // don't animate, implement no animation
//    newObj->hbmMask_ = NULL;
//    newObj->max = 1;
//    newObj->X = 0;
//    newObj->leftSide = 17;
//    newObj->rightSide = 48;
//    newObj->topSide = -23;
//    newObj->bottomSide = 25;
//    if(outline)
//        newObj->outline = true;
//    objects.push_back(newObj);
////    std::cout << "pipe.topside: " << (newObj->y + newObj->topSide) << std::endl;
//    return newObj;
//}
//
//void GenerateCoin(int x, int y, bool dying)
//{
//    BITMAP bitmap;
//    Object* newObj = new Object();
//    newObj->x = x;
//    newObj->y = y;
//    newObj->dy = -15;
//    newObj->hbm_ = coin;
//    newObj->hbmMask_ = coinMask;
//    GetObject(newObj->hbm_, sizeof(BITMAP), &bitmap);
//    newObj->width = bitmap.bmWidth/5;
//    newObj->height = bitmap.bmHeight;
//    newObj->max = 5;
//    newObj->X = 0;
//    if(dying)
//        newObj->cyclesUntilDeath = 10;
//    if(outline)
//        newObj->outline = true;
//    newObj->typeOfObject = COIN;
//    objects.push_back(newObj);
//}
//
//void GenerateFlowerEnemy(int x, int y, void* p)
//{
//    BITMAP bitmap;
//    Object *newObj = new Object();
//    newObj->typeOfObject = FLOWER_ENEMY;
//    newObj->x = x;
//    newObj->startingY = newObj->y = y;
//    newObj->dy = -3;
//    newObj->hbm_ = enemy;
//    newObj->hbmMask_ = enemyMask;
//    GetObject(newObj->hbm_, sizeof(BITMAP), &bitmap);
//    newObj->width = bitmap.bmWidth/6;
//    newObj->height = bitmap.bmHeight;
//    newObj->max = 2;
//    newObj->X = 0;
//    newObj->leftSide = -1;
//    newObj->rightSide = 17;
//    newObj->topSide = -1;
//    newObj->bottomSide = 35;
//    newObj->cyclesForChange = 10;
//    newObj->parent = p;
////    newObj->changeCycles = 0;
//    if(outline)
//        newObj->outline = true;
//    objects.push_back(newObj);
//}
//
//void GenerateGoomba(int x, int y)
//{
//    BITMAP bitmap;
//    Object *newObj = new Object();
//    newObj->typeOfObject = GOOMBA;
//    newObj->x = newObj->startingX = x;
//    newObj->startingY = newObj->y = y;
//    newObj->dy = 0;
//    newObj->dx = -3;
//    newObj->hbm_ = goomba;
//    newObj->hbmMask_ = goombaMask;
//    GetObject(newObj->hbm_, sizeof(BITMAP), &bitmap);
//    newObj->width = bitmap.bmWidth/4;
//    newObj->height = bitmap.bmHeight;
//    newObj->max = 2;
//    newObj->X = 0;
//    if(outline)
//        newObj->outline = true;
////    newObj->changeCycles = 0;
//    objects.push_back(newObj);
//}

//void GenerateHill(int x, int y)
//{
//    BITMAP bitmap;
//    Object *newObj = new Object();
//    newObj->typeOfObject = HILL;
//    newObj->x = newObj->startingX = x;
//    newObj->startingY = newObj->y = y;
//    newObj->dy = 0;
//    newObj->dx = 0;
//    newObj->hbm_ = goomba;
//    newObj->hbmMask_ = goombaMask;
//    GetObject(newObj->hbm_, sizeof(BITMAP), &bitmap);
//    newObj->width = bitmap.bmWidth;
//    newObj->height = bitmap.bmHeight;
//    newObj->max = 0;
//    newObj->X = 0;
//    newObj->cyclesForChange = 0;
//    objects.push_back(newObj);
//}

//void GenerateGround(int x, int y)
//{
//    BITMAP bitmap;
//    Object *newObj = new Object();
//    newObj->typeOfObject = GROUND;
//    newObj->x = newObj->startingX = x;
//    newObj->startingY = newObj->y = y;
//    newObj->dy = 0;
//    newObj->dx = 0;
//    newObj->hbm_ = ground;
//    newObj->hbmMask_ = groundMask;
//    GetObject(newObj->hbm_, sizeof(BITMAP), &bitmap);
//    newObj->width = bitmap.bmWidth;
//    newObj->height = bitmap.bmHeight;
//    newObj->max = 1;
//    newObj->X = 0;
//    newObj->bottomSide = 20;
//    newObj->topSide = 0;
//    newObj->leftSide = 0;
//    newObj->rightSide = 53;
////    newObj->changeCycles = 0;
//    if(outline)
//        newObj->outline = true;
//    objects.push_back(newObj);
//}

//void GenerateObjects()
//{
////    GenerateQuestionMark(176, 201);
////    GenerateQuestionMark(193, 201);
////    GenerateQuestionMark(224, 153);
////    GenerateQuestionMark(240, 153);
////    GenerateQuestionMark(416, 169);
////    GenerateQuestionMark(120, 201);
////    void* p = GeneratePipe(335, 240);
////    GenerateFlowerEnemy(359, 221, p);
////    GenerateGround(25, 200);
////
////
////    objects.push_back(initial_ground_first);
////    objects.push_back(initial_ground_second);
////    objects.push_back(initial_ground_third);
////    objects.push_back(death_ground);
//
//
//
////    newObj = new Object();
////    newObj->typeOfObject = GROUND;
////    newObj->x = 30;
////    newObj->startingY = newObj->y = 263;
////    newObj->dy = 0;
////    newObj->hbm_ = (HBITMAP) LoadImage(NULL, "ground.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
////    newObj->hbmMask_ = (HBITMAP) LoadImage(NULL, "groundBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
////    GetObject(newObj->hbm_, sizeof(BITMAP), &bitmap);
////    newObj->width = bitmap.bmWidth;
////    newObj->height = bitmap.bmHeight;
////    newObj->max = 0;
////    newObj->X = 0;
////    objects.push_back(newObj);
//}
