#include "PiranhaTimerUp.hpp"

void CALLBACK PiranhaTimerUp(HWND hwnd, UINT message, UINT idTimer, DWORD dwTime)
{
    std::cout << "PiranhaTimerUp/piranha now is going down" << std::endl;
    idTimer->dy = 3;
}
