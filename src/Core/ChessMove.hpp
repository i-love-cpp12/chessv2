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

    inline ChessMoveType operator|(ChessMoveType a, ChessMoveType b)
    {
        return static_cast<ChessMoveType>(
            static_cast<uint8_t>(a) |
            static_cast<uint8_t>(b)
        );
    }

    class ChessMove
    {
        public:
            ChessMove(const ChessboardPosition& source, const ChessboardPosition& destination, const ChessMoveType moveType = ChessMoveType::NONE, const std::optional<PieceType>& capturedPieceType = std::nullopt);
        public:
            ChessboardPosition source;
            ChessboardPosition destination;
            ChessMoveType moveType;
            std::optional<PieceType> capturedPieceType;
    };
}