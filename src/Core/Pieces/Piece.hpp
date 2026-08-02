#pragma once
#include<cstdint>
#include<vector>
#include"../ChessboardPosition.hpp"
#include<memory>

namespace Chess
{
    class ChessMove;
    class Board;

    enum PieceColor : uint8_t
    {
        CHESS_WHITE,
        CHESS_BLACK
    };

    enum PieceType: uint8_t
    {
        KING,
        QUEEN,
        ROOK,
        BISHOP,
        KNIGHT,
        PAWN
    };

    class Piece
    {
        public:
            Piece(const PieceColor color, const PieceType type, const Board& board, const ChessboardPosition& position);
            Piece(const Piece& other) = default;
            virtual ~Piece() = default;
            virtual std::unique_ptr<Piece> clone() const = 0;
            virtual std::vector<Chess::ChessMove> getPseudoPossibleMoves() const = 0;
            virtual void setPosition(const ChessboardPosition& dest);
            ChessboardPosition getPosition() const { return position; }
            constexpr virtual char getPieceCharRepresentation() const = 0;
            constexpr virtual bool hasMoved() const { return true; };
            
        public:
            const PieceColor color;
            const PieceType type;
        protected:
            const Board& board;
            ChessboardPosition position;

    };
}