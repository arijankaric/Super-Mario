#include "../include/Game.hpp"

void Game::PiranhaTimerDown(HWND hwnd, UINT message, UINT idTimer, DWORD dwTime)
{
    Object* flowerEnemy = ((Object*)idTimer);
    Object* pipe = ((Object*)flowerEnemy->parent);
    std::cout << "distance between Mario and piranha: " << distanceBetweenObjects(mario.get(), flowerEnemy) << std::endl;
    if (distanceBetweenObjects(mario.get(), flowerEnemy) < 50 || ((pipe->y + pipe->topSide) == mario->ground))
    {
        std::cout << "Piranha is not going up since Mario is too close or Mario hasn't changed his footing yet" << std::endl;
        SetTimer(hwnd, (UINT_PTR)idTimer, 1000, (TIMERPROC)&Game::StaticPiranhaTimerDown);
        return;
    }
    std::cout << "PiranhaTimerDown/piranha is now going up" << std::endl;
    flowerEnemy->dy_ = -3;
    flowerEnemy->flag = true; // piranha is active
}

void CALLBACK Game::StaticPiranhaTimerDown(HWND hwnd, UINT message, UINT idTimer, DWORD dwTime) {
  Game* pThis = (Game*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
  pThis->PiranhaTimerDown(hwnd, message, idTimer, dwTime);
}
