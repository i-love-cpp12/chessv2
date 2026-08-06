#pragma once
#include<cstdint>
#include<vector>
#include"../ChessboardPosition.hpp"
#include<memory>
#include<span>
#include"../UniversalVector.hpp"

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
            ChessboardPosition getPosition() const { return position; }
            constexpr virtual char getPieceCharRepresentation() const = 0;
            constexpr virtual bool hasMoved() const { return true; };
        protected:
            virtual void setPosition(const ChessboardPosition& dest);
            std::vector<Chess::ChessMove> getMovesBasedOfDirs(const std::span<const UniversalVector<int8_t>> dirs) const;
            std::vector<Chess::ChessMove> getMovesBasedOfOffsets(const std::span<const UniversalVector<int8_t>> offsets) const;

        public:
            const PieceColor color;
            const PieceType type;
        protected:
            static constexpr std::array<UniversalVector<int8_t>, 4> diagonalDirs = {
                UniversalVector<int8_t>{-1, -1},
                UniversalVector<int8_t>{1, -1},
                UniversalVector<int8_t>{-1, 1},
                UniversalVector<int8_t>{1, 1}
            };

            static constexpr std::array<UniversalVector<int8_t>, 4> straightDirs = {
                UniversalVector<int8_t>{1, 0},
                UniversalVector<int8_t>{-1, 0},
                UniversalVector<int8_t>{0, -1},
                UniversalVector<int8_t>{0, 1}
            };

            static constexpr std::array<UniversalVector<int8_t>, 8> combinedDirs{
                UniversalVector<int8_t>{-1, -1},
                UniversalVector<int8_t>{1, -1},
                UniversalVector<int8_t>{-1, 1},
                UniversalVector<int8_t>{1, 1},
                UniversalVector<int8_t>{1, 0},
                UniversalVector<int8_t>{-1, 0},
                UniversalVector<int8_t>{0, -1},
                UniversalVector<int8_t>{0, 1}
            };

            const Board& board;
            ChessboardPosition position;
        
        friend Board;
    };
}