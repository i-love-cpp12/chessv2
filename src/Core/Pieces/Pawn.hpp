#pragma once

#include"Piece.hpp"
#include<vector>
#include<array>
#include<memory>
#include"../UniversalVector.hpp"

namespace Chess
{
    class Pawn : public Piece
    {
        public:
            Pawn(const PieceColor color, const Board& board, const ChessboardPosition& position);
            std::unique_ptr<Piece> clone() const override;
            std::vector<ChessMove> getPseudoPossibleMoves() const override;
            constexpr char getPieceCharRepresentation() const override { return '\0';}
            constexpr bool hasMoved() const override { return _hasMoved; }
            bool isPromoting(const ChessboardPosition& futurePosition) const;
        protected:
            void setPosition(const ChessboardPosition& dest) override;
        private:
            bool _hasMoved;
    };
}