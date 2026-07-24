#include"raylib.h"
#include"Board.hpp"
#include<iostream>

int main()
{
    Chess::Board().generateBoard();
    std::cin.get();
    return 0;
}