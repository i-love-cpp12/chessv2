#pragma once

#include"Piece.hpp"
#include<vector>
#include<array>
#include<memory>
#include"../UniversalVector.hpp"

namespace Chess
{
    class Bishop : public Piece
    {
        public:
            Bishop(const PieceColor color, const Board* board, const ChessboardPosition& position);
            std::unique_ptr<Piece> clone(const Board* newBoard = nullptr) const override;
            std::vector<ChessMove> getPseudoPossibleMoves() const override;
            constexpr char getPieceCharRepresentation() const override { return 'B';}
            constexpr bool hasMoved() const override { return true; }
    };
}