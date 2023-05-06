#pragma once

#include <fstream>
#include <sstream>
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
    Object::vektorObjekata objects = std::make_shared<std::vector<std::shared_ptr<Object>>>(); // static or soon to die objects that we don't care if they collide or not (old idea)
    Object::vektorObjekata movingObjects = std::make_shared<std::vector<std::shared_ptr<Object>>>(); // for example Mario and Goombas/Turtles (old idea)
    Object::vektorObjekata newObjects = std::make_shared<std::vector<std::shared_ptr<Object>>>(); // new objects to be added to objects in next iteration of update such as fireball

    std::shared_ptr<Object> mario = std::make_shared<Mario>();
    std::shared_ptr<Object> background = std::make_shared<Background>();
    int initial_ground = 164;
//    friend class Object;

//    const int ID_TIMER = 1; // moramo razmislit kako cemo i sta cemo sa timera, da li cemo ih ubacit u ovu klasu ili?
//    const int IDT_TIMER3 = 50;
//    const int ID_TIMER_PIRANHA_UP = 0;
//    const int ID_TIMER_PIRANHA_DOWN = 1;

    const int dx_ = 1;
    const int dy_ = 1;

    RECT* clientRect;
    void GenerateObjects();
    void generateObjects(const std::string& configFile);
    struct ObjectArgs
    {
        std::string type;
        std::vector<std::string> args;
    };
public:
    HWND hwnd;
    Game();
    void CheckInput(void);
    void Update(void);
    void UpdateObjekat();
    void Render(void);
    void DrawObjekat(HDC hdc);
    void UpdatePositionOfObjects(int dx_, int dy_);
    void praviUpdate();
    void PiranhaTimerDown(HWND hwnd, UINT message, UINT idTimer, DWORD dwTime);
    void PiranhaTimerUp(HWND hwnd, UINT message, UINT idTimer, DWORD dwTime);
    static void CALLBACK StaticPiranhaTimerDown(HWND hwnd, UINT message, UINT idTimer, DWORD dwTime);
    static void CALLBACK StaticPiranhaTimerUp(HWND hwnd, UINT message, UINT idTimer, DWORD dwTime);
};
