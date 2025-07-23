// SFMLMatchGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Game.h"


int main()
{
    constexpr float kScreenWidth{ 400.0f };
    constexpr float kScreenHeight{ 800.0f };
    
    constexpr int kFrameTarget{ 60 };
    constexpr int kRowCount{ 5 };
    constexpr int kColCount{ 6 };

    Game newGame;
    //newGame.Start(kScreenWidth, kScreenHeight, "SFMLMatchGame", kRowCount, kColCount);
    //newGame.Update(kFrameTarget);
    newGame.Run(kScreenWidth, kScreenHeight, kFrameTarget, "SFMLMatchGame", kRowCount, kColCount);

    return 0;
}

