// SFMLMatchGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Game.h"


int main()
{
    constexpr int kScreenWidth{ 400 };
    constexpr int kScreenHeight{ 700 };
    
    constexpr int kFrameTarget{ 60 };

    Game newGame;
    //newGame.Start(kScreenWidth, kScreenHeight, "SFMLMatchGame", kRowCount, kColCount);
    //newGame.Update(kFrameTarget);
    newGame.Run(kScreenWidth, kScreenHeight, kFrameTarget, "SFMLMatchGame");

    return 0;
}

