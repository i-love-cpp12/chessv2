#pragma once

#include"ChessboardPosition.hpp"
#include"Pieces/Piece.hpp"
#include<optional>

namespace Chess
{
    enum ChessMoveType : uint8_t
    {
        NONE = 0,
        CAPTURE = 1 << 0,
        PROMOTION = 1 << 1,
        EN_PASSANT = 1 << 2,
        LONG_CASTLE = 1 << 3,
        SHORT_CASTLE = 1 << 4
    };

    class ChessMove
    {
        public:
            ChessMove(const ChessboardPosition& destination, const Piece& piece, const ChessMoveType moveType = ChessMoveType::NONE, const std::optional<PieceType>& capturedPieceType = std::nullopt);
        public:
            const ChessboardPosition destination;
            const Piece& piece;
            const ChessboardPosition& source;
        private:
            ChessMoveType moveType;
            const std::optional<PieceType> capturedPieceType;
    };
}