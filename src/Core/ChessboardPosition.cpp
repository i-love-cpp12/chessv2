#include"ChessboardPosition.hpp"
#include"Board.hpp"
#include<stdexcept>
#include<cctype>

Chess::ChessboardPosition::ChessboardPosition(uint8_t x, uint8_t y)
{
    setPosition(x, y);
}

Chess::ChessboardPosition::ChessboardPosition(const UniversalVector<uint8_t> &pos)
{
    setPosition(pos);
}

Chess::ChessboardPosition::ChessboardPosition(const std::string &chessNotationPosition)
{
    setPosition(chessNotationPosition);
}

bool Chess::ChessboardPosition::operator==(const ChessboardPosition &other)
{
    return x == other.x && y == other.y;
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

void Chess::ChessboardPosition::setPosition(const UniversalVector<uint8_t> &pos)
{
    setPosition(pos.x, pos.y);
}

void Chess::ChessboardPosition::setPosition(const std::string &chessNotationPosition)
{
    if(chessNotationPosition.size() < 2)
        throw std::runtime_error("Invalid chess notation");

    char colChar = std::toupper(chessNotationPosition[0]);
    char rowChar = std::toupper(chessNotationPosition[1]);

    size_t x = colsCharsChessNotation.find(colChar);
    size_t y = rowsCharsChessNotation.find(rowChar);

    if(x == colsCharsChessNotation.npos || y == rowsCharsChessNotation.npos)
        throw std::runtime_error("Invalid chess notation");

    setPosition(x, y);
}