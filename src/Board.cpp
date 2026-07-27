#include"Board.hpp"
#include"../libs/json.hpp"
#include<fstream>
#include<stdexcept>


#include<iostream>
Chess::Board::Board(const std::string &boardSetupFilePath)
{
    generateBoard(boardSetupFilePath);
}

void Chess::Board::generateBoard(const std::string &boardSetupFilePath)
{
    std::ifstream setupJSONFile(boardSetupFilePath);

    if(!setupJSONFile)
        throw std::runtime_error("Failed to load boardSetupFilePath");
    
    nlohmann::json JSON;
    setupJSONFile >> JSON;

    std::cout<<JSON.dump();
}

bool Chess::Board::inBoardBounds(uint8_t x, uint8_t y)
{
    return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT;
}

bool Chess::Board::inBoardBounds(const UniversalVector<uint8_t>& pos)
{
    return inBoardBounds(pos.x, pos.y);
}

const Chess::Piece* Chess::Board::getPiece(uint8_t x, uint8_t y) const
{
    if(!inBoardBounds(x, y))
        throw std::runtime_error("Position out of bound");
        
    return data[y * WIDTH + x].get();
}

const Chess::Piece *Chess::Board::getPiece(const UniversalVector<uint8_t>&  pos) const
{
    return getPiece(pos.x, pos.y);
}

void Chess::Board::movePiece(ChessboardPosition from, ChessboardPosition to)
{
    std::unique_ptr<Chess::Piece>& source = data[from.getY() * WIDTH + from.getX()];
    std::unique_ptr<Chess::Piece>& dest = data[to.getY() * WIDTH + to.getX()];

    dest = std::move(source);

    if(dest)
        dest->setPosition(to);
}
