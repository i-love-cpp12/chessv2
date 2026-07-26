#include"ChessPosition.hpp"
#include"Board.hpp"
#include<stdexcept>

std::string Chess::ChessboardPosition::rowsCharsChessNotation = "87654321";
std::string Chess::ChessboardPosition::colsCharsChessNotation = "ABCDEFGH";

Chess::ChessboardPosition::ChessboardPosition(uint8_t x, uint8_t y)
{
    setPosition(x, y);
}

Chess::ChessboardPosition::ChessboardPosition(const std::string &chessNotationPosition)
{
    setPosition(chessNotationPosition);
}

std::string Chess::ChessboardPosition::getChessNotationPosition()
{
    return std::string{colsCharsChessNotation[x], rowsCharsChessNotation[y]};
}

void Chess::ChessboardPosition::setPosition(uint8_t x, uint8_t y)
{
    if(!Board::inBoardBounds(x, y))
        throw std::runtime_error("Position out of bound");

    this->x = x;
    this->y = y;
}

void Chess::ChessboardPosition::setPosition(const std::string &chessNotationPosition)
{
    if(chessNotationPosition.size() < 2)
        std::runtime_error("Invalid chess notation");

    char colChar = chessNotationPosition[0];
    char rowChar = chessNotationPosition[1];

    uint8_t x = colsCharsChessNotation.find(colChar);
    if(x == colsCharsChessNotation.npos)
        std::runtime_error("Invalid chess notation");
    
    uint8_t y = rowsCharsChessNotation.find(rowChar);
    if(y == rowsCharsChessNotation.npos)
        std::runtime_error("Invalid chess notation");

    setPosition(x, y);
}