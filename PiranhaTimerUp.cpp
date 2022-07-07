#include "Game.hpp"

void CALLBACK Game::PiranhaTimerUp(HWND hwnd, UINT message, UINT idTimer, DWORD dwTime)
{
    std::cout << "PiranhaTimerUp/piranha is now going down" << std::endl;
    ((Object*)idTimer)->dy = 3;
}
