#include"Board.hpp"
#include"../libs/json.hpp"
#include<fstream>
#include<stdexcept>


#include<iostream>

void Chess::Board::generateBoard(const std::string &boardSetupFilePath)
{
    std::ifstream setupJSONFile(boardSetupFilePath);

    if(!setupJSONFile)
        throw std::runtime_error("Failed to load boardSetupFilePath");
    
    nlohmann::json JSON;
    setupJSONFile >> JSON;

    std::cout<<JSON.dump();
}

Chess::Piece* Chess::Board::getPieceRef(uint8_t x, uint8_t y) const
{
    if(!inBoardBounds(x, y))
        throw std::runtime_error("Position out of bound");
        
    return data[y * WIDTH + x].get();
}

bool Chess::Board::inBoardBounds(uint8_t x, uint8_t y)
{
    return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT;
}

const Chess::Piece* Chess::Board::getPiece(uint8_t x, uint8_t y) const
{
    return getPieceRef(x, y);
}

bool Chess::Board::isEnPassantPosition(uint8_t x, uint8_t y) const
{
    return enPassantPosition && enPassantPosition->getX() == x && enPassantPosition->getY() == y;
}
