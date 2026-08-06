#pragma once

#include"Piece.hpp"
#include<vector>
#include<array>
#include<memory>
#include"../UniversalVector.hpp"

namespace Chess
{
    class Knight : public Piece
    {
        public:
            Knight(const PieceColor color, const Board& board, const ChessboardPosition& position);
            std::unique_ptr<Piece> clone() const override;
            std::vector<ChessMove> getPseudoPossibleMoves() const override;
            constexpr char getPieceCharRepresentation() const override { return 'N';}
            constexpr bool hasMoved() const override { return true; }
        private:
        static constexpr std::array<UniversalVector<int8_t>, 8> offsets = {
            UniversalVector<int8_t>{1, 2},
            UniversalVector<int8_t>{-1, 2},
            UniversalVector<int8_t>{1, -2},
            UniversalVector<int8_t>{-1, -2},
            UniversalVector<int8_t>{2, 1},
            UniversalVector<int8_t>{-2, 1},
            UniversalVector<int8_t>{2, -1},
            UniversalVector<int8_t>{-2, -1}
        };
    };
}