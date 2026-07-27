#include"raylib.h"
#include"Core/Board.hpp"
#include"Core/ChessboardPosition.hpp"
#include<iostream>

int main()
{
    Chess::Board();
    // std::cout<<Chess::ChessboardPosition("e4").getChessNotationPosition()<<" "<<(int)Chess::ChessboardPosition(1, 9).getX()<<" "<<(int)Chess::ChessboardPosition(1, 9).getY();
    std::cin.get();
    return 0;
}