#pragma once

#include"Piece.hpp"
#include<vector>
#include<array>
#include"UniversalVector.hpp"

namespace Chess
{
    class Pawn : public Piece
    {
        public:
            Pawn(const PieceColor color, const PieceType type, const Board& board, const ChessboardPosition& position);
            std::vector<ChessMove> getPseudoPossibleMoves() const override;
            void setPosition(const ChessboardPosition& dest) override;
            constexpr char getPieceCharRepresentation() const override { return '\0';}
            constexpr bool hasMoved() const override { return _hasMoved; }
            bool isPromoting(const ChessboardPosition& futurePosition) const;
        private:
            bool _hasMoved;
    };
}