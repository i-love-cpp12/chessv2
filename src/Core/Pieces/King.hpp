#pragma once

#include"Piece.hpp"
#include<vector>
#include<array>
#include<memory>
#include"../UniversalVector.hpp"

namespace Chess
{
    class King : public Piece
    {
        public:
            King(const PieceColor color, const Board* board, const ChessboardPosition& position);
            std::unique_ptr<Piece> clone(const Board* newBoard = nullptr) const override;
            std::vector<ChessMove> getPseudoPossibleMoves() const override;
            constexpr char getPieceCharRepresentation() const override { return 'K';}
            constexpr bool hasMoved() const override { return _hasMoved; }
        private:
            void setPosition(const ChessboardPosition& dest) override;
            static constexpr std::array<UniversalVector<int8_t>, 8> offsets = {
                UniversalVector<int8_t>{-1, -1},
                UniversalVector<int8_t>{0, -1},
                UniversalVector<int8_t>{1, -1},
                UniversalVector<int8_t>{-1, 0},
                UniversalVector<int8_t>{1, 0},
                UniversalVector<int8_t>{-1, 1},
                UniversalVector<int8_t>{0, 1},
                UniversalVector<int8_t>{1, 1}
            };
            bool _hasMoved;
    };
}