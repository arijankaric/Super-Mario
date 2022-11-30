#pragma once

#include "Mario.hpp"
#include "Pipe.hpp"
#include "Goomba.hpp"
#include "QuestionBlock.hpp"
#include "Coin.hpp"
#include "FlowerEnemy.hpp"
#include "Ground.hpp"
#include "Turtle.hpp"

class Game
{
private:
//    using vektorObjekata = std::shared_ptr<std::vector<std::shared_ptr<Object>>>;
    Object::vektorObjekata objects = std::make_shared<std::vector<std::shared_ptr<Object>>>(); // static or soon to die objects that we don't care if they collide or not
    Object::vektorObjekata movingObjects = std::make_shared<std::vector<std::shared_ptr<Object>>>(); // for example Mario and Goombas/Turtles
    std::shared_ptr<Object> mario = std::make_shared<Mario>();
    std::shared_ptr<Object> background = std::make_shared<Background>();
    int initial_ground = 164;
//    friend class Object;

//    const int ID_TIMER = 1; // moramo razmislit kako cemo i sta cemo sa timera, da li cemo ih ubacit u ovu klasu ili?
//    const int IDT_TIMER3 = 50;
//    const int ID_TIMER_PIRANHA_UP = 0;
//    const int ID_TIMER_PIRANHA_DOWN = 1;

    const int DX = 1;
    const int DY = 1;

    RECT* clientRect;
    void GenerateObjects();
public:
    HWND hwnd;
    Game();
    void CheckInput(void);
    void Update(void);
    void UpdateObjekat();
    void Render(void);
    void DrawObjekat(HDC hdc);
    bool UpdatePositionOfObjects(int dx, int dy);
    void praviUpdate();
    void CALLBACK PiranhaTimerDown(HWND hwnd, UINT message, UINT idTimer, DWORD dwTime);
    void CALLBACK PiranhaTimerUp(HWND hwnd, UINT message, UINT idTimer, DWORD dwTime);
};
