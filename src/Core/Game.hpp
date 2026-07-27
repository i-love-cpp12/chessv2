#pragma once

#include<vector>
#include"Board.hpp"
#include"Pieces/Piece.hpp"
#include"ChessMove.hpp"

namespace Chess
{
    class Game
    {
        public: 
            Game();
            const std::vector<ChessMove>& getPossibleMoves() const { return posibleMoves; }
            // bool isCheckmate() const;
            // bool isCheck() const;
            PieceColor getTurn() const { return turn; }
            void onSquereSelected(uint8_t x, uint8_t y);
            const Board& getBoard() const { return board; }
        private:
            void makeMove(const ChessMove& move);
            bool isEnPassantPosition(uint8_t x, uint8_t y) const;
        public:

        private:
            Board board;
            std::vector<ChessMove> posibleMoves;
            std::optional<ChessboardPosition> enPassantPosition;
            std::optional<ChessboardPosition> selectedSquere;
            PieceColor turn;
    };
}