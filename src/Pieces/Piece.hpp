#pragma once
#include<cstdint>
#include<vector>

namespace Chess
{
    struct PieceMove;
    class Board;

    enum PieceColor : uint8_t
    {
        WHITE1,
        BLACK1
    };

    enum PieceType: uint8_t
    {
        KING,
        QWEEN,
        ROOK,
        BISHOP,
        KNIGHT,
        PAWN
    };

    class Piece
    {
        public:
            Piece(const PieceColor color, const PieceType type, Board& board, const uint8_t x, const uint8_t y);
            virtual ~Piece() = default;
            virtual std::vector<PieceMove> getPossbileMoves() const = 0;
            
        private:

        public:
            const PieceColor color;
            const PieceType type;
        private:
            Board& board;
            uint8_t x;
            uint8_t y;

    };
}