#include "../include/Game.hpp"

void CALLBACK Game::PiranhaTimerUp(HWND hwnd, UINT message, UINT idTimer, DWORD dwTime)
{
    std::cout << "PiranhaTimerUp/piranha is now going down " << ((Object*)idTimer)->dy_ << " kraj" << std::endl;
    ((Object*)idTimer)->dy_ = 3;
}
