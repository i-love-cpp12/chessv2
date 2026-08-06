#pragma once

#include"Piece.hpp"
#include<vector>
#include<array>
#include<memory>
#include"../UniversalVector.hpp"

namespace Chess
{
    class Rook : public Piece
    {
        public:
            Rook(const PieceColor color, const Board& board, const ChessboardPosition& position);
            std::unique_ptr<Piece> clone() const override;
            std::vector<ChessMove> getPseudoPossibleMoves() const override;
            constexpr char getPieceCharRepresentation() const override { return 'R';}
            constexpr bool hasMoved() const override { return _hasMoved; }
        private:
            void setPosition(const ChessboardPosition& dest) override;
            bool _hasMoved;
    };
}