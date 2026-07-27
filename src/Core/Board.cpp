#include"Board.hpp"
#include"../../libs/json.hpp"
#include<fstream>
#include<stdexcept>
#include<cctype>
#include"Pieces/Pawn.hpp"


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

    if(!JSON.is_array() || JSON.size() != HEIGHT)
        throw std::runtime_error("Invalid format for board setup");
    for(uint8_t y = 0; y < HEIGHT; ++y)
    {
        if(!JSON[y].is_array() || JSON[y].size() != WIDTH)
            throw std::runtime_error("Invalid format for board setup");
        for(uint8_t x = 0; x < WIDTH; ++x)
        {
            char piceChar = std::string(JSON[y][x])[0];
            std::cout<<piceChar<<", ";
            data[y * HEIGHT + x] = std::move(pieceFactory(piceChar, ChessboardPosition(x, y)));
        }
    }
}

std::unique_ptr<Chess::Piece> Chess::Board::pieceFactory(char type, const ChessboardPosition& position) const
{
    const PieceColor color = std::isupper(type) ? PieceColor::CHESS_WHITE : PieceColor::CHESS_BLACK;

    type = std::toupper(type);

    switch(type)
    {
        case 'K':
            return nullptr;

        case 'Q':
            return nullptr;

        case 'R':
            return nullptr;

        case 'B':
            return nullptr;

        case 'N':
            return nullptr;

        case 'P':
            return std::make_unique<Pawn>(color, *this, position);

        case ' ':
            return nullptr;

        default:
            throw std::runtime_error("Invalid piece character");
    }
}

bool Chess::Board::inBoardBounds(int8_t x, int8_t y)
{
    return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT;
}

bool Chess::Board::inBoardBounds(const UniversalVector<int8_t>& pos)
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

void Chess::Board::movePiece(const ChessboardPosition& from, const ChessboardPosition& to)
{
    std::unique_ptr<Chess::Piece>& source = data[from.getY() * WIDTH + from.getX()];
    std::unique_ptr<Chess::Piece>& dest = data[to.getY() * WIDTH + to.getX()];

    dest = std::move(source);

    if(dest)
        dest->setPosition(to);
}
