// SFMLMatchGame.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "Game.h"

int main()
{
    constexpr int kScreenWidth{ 400 };
    constexpr int kScreenHeight{ 650 };
    
    constexpr int kFrameTarget{ 60 };

    Game newGame(kScreenWidth, kScreenHeight, kFrameTarget, "SFMLMatchGame", kFrameTarget);
    newGame.Run();

    return 0;
}
