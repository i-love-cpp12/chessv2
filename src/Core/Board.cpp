#include"Board.hpp"
#include"../../libs/json.hpp"
#include<fstream>
#include<stdexcept>
#include<cctype>
#include"Pieces/Pawn.hpp"
#include"Pieces/King.hpp"
#include"Pieces/Queen.hpp"
#include"Pieces/Rook.hpp"
#include"Pieces/Bishop.hpp"
#include"Pieces/Knight.hpp"


#include<iostream>
Chess::Board::Board(const std::string &boardSetupFilePath)
{
    generateBoard(boardSetupFilePath);
}

Chess::Board::Board(const Board &other)
{
    for(size_t i = 0; i < data.size(); ++i)
    {
        if(other.data[i])
            data[i] = other.data[i]->clone(this);
    }
    whiteKing = getPiece(other.whiteKing->getPosition());
    blackKing = getPiece(other.blackKing->getPosition());
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
    for(int8_t y = 0; y < HEIGHT; ++y)
    {
        if(!JSON[y].is_array() || JSON[y].size() != WIDTH)
            throw std::runtime_error("Invalid format for board setup");
        for(int8_t x = 0; x < WIDTH; ++x)
        {
            char piceChar = std::string(JSON[y][x])[0];
            std::cout<<piceChar<<", ";
            data[y * HEIGHT + x] = std::move(pieceFactory(piceChar, ChessboardPosition(x, y)));

            const Piece* curr = data[y * HEIGHT + x].get();
            if(curr && curr->type == PieceType::KING)
            {
                if(curr->color == PieceColor::CHESS_WHITE)
                    whiteKing = curr;
                else
                    blackKing = curr;
            }
        }
    }
}

constexpr Chess::PieceType Chess::Board::charToPieceType(char type)
{
    type = std::toupper(type);

    switch(type)
    {
        case 'K': return PieceType::KING;
        case 'Q': return PieceType::QUEEN;
        case 'R': return PieceType::ROOK;
        case 'B': return PieceType::BISHOP;
        case 'N': return PieceType::KNIGHT;
        case 'P': return PieceType::PAWN;
        case ' ': return PieceType::EMPTY;
        default: throw std::runtime_error("Invalid piece character");
    }
}

std::unique_ptr<Chess::Piece> Chess::Board::pieceFactory(char charType, const ChessboardPosition& position) const
{
    const PieceColor color = std::isupper(charType) ? PieceColor::CHESS_WHITE : PieceColor::CHESS_BLACK;

    const PieceType type = charToPieceType(charType);

    return pieceFactory(type, color, position);
}

std::unique_ptr<Chess::Piece> Chess::Board::pieceFactory(PieceType type, PieceColor color, const ChessboardPosition &position) const
{
    switch(type)
    {
        case PieceType::KING:
            return std::make_unique<Chess::King>(color, this, position);

        case PieceType::QUEEN:
            return std::make_unique<Chess::Queen>(color, this, position);

        case PieceType::ROOK:
            return std::make_unique<Chess::Rook>(color, this, position);

        case PieceType::BISHOP:
            return std::make_unique<Chess::Bishop>(color, this, position);

        case PieceType::KNIGHT:
            return std::make_unique<Chess::Knight>(color, this, position);

        case PieceType::PAWN:
            return std::make_unique<Chess::Pawn>(color, this, position);

        case PieceType::EMPTY:
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

void Chess::Board::foreachSquare(std::function<bool(const Piece *)> callback) const
{
    for(int8_t y = 0; y < HEIGHT; ++y)
    {
        for(int8_t x = 0; x < WIDTH; ++x)
        {
            if(callback(getPiece(x, y)))
                return;
        }
    }
}

const Chess::Piece* Chess::Board::getPiece(int8_t x, int8_t y) const
{
    if(!inBoardBounds(x, y))
        throw std::runtime_error("Position out of bound");
        
    return data[y * WIDTH + x].get();
}

const Chess::Piece* Chess::Board::getPiece(const UniversalVector<int8_t>&  pos) const
{
    return getPiece(pos.x, pos.y);
}

const Chess::Piece *Chess::Board::getPiece(const ChessboardPosition &pos) const
{
    return getPiece(pos.getX(), pos.getY());
}

const Chess::Piece& Chess::Board::getKing(const PieceColor color) const
{
    return *(color == PieceColor::CHESS_WHITE ? whiteKing : blackKing);
}

void Chess::Board::removePiece(int8_t x, int8_t y)
{
    if(!inBoardBounds(x, y))
        throw std::runtime_error("Position out of bound");
        
    data[y * WIDTH + x].reset();
}

void Chess::Board::removePiece(const UniversalVector<int8_t> &pos)
{
    removePiece(pos.x, pos.y);
}

void Chess::Board::setPiece(int8_t x, int8_t y, PieceType type, PieceColor color)
{
    if(!inBoardBounds(x, y))
        throw std::runtime_error("Position out of bound");

    data[y * WIDTH + x] = std::move(pieceFactory(type, color, ChessboardPosition(x, y)));
}

void Chess::Board::setPiece(ChessboardPosition position, PieceType type, PieceColor color)
{
    setPiece(position.getX(), position.getY(), type, color);
}

void Chess::Board::setPiece(const UniversalVector<int8_t>& position, PieceType type, PieceColor color)
{
    setPiece(position.x, position.y, type, color);
}

void Chess::Board::movePiece(const ChessboardPosition &from, const ChessboardPosition &to)
{
    std::unique_ptr<Chess::Piece>& source = data[from.getY() * WIDTH + from.getX()];
    std::unique_ptr<Chess::Piece>& dest = data[to.getY() * WIDTH + to.getX()];

    dest = std::move(source);

    if(dest)
        dest->setPosition(to);
}
