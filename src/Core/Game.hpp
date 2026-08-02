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
            // const std::vector<ChessMove>& getPossibleMoves() const { return posibleMoves; }
            const std::optional<ChessboardPosition> getSelectedSquere() const { return selectedPieceSquere; }
            PieceColor getTurn() const { return turn; }
            void onSquereSelected(uint8_t x, uint8_t y);
            const Board& getBoard() const { return board; }

            //get filtered pseudo moves
            std::vector<ChessMove> getPossibleMovesFor(const Piece* piece) const;
            std::vector<ChessMove> getPossibleMovesFor(uint8_t x, uint8_t y) const;
            std::vector<ChessMove> getPossibleMovesFor(const UniversalVector<uint8_t>& position) const;
            std::vector<ChessMove> getPossibleMovesFor(const ChessboardPosition& position) const;

        private:
            void makeMove(const ChessMove& move);
            bool isCheck(const PieceColor& colorInCheck, const std::optional<Board>& board) const;
            bool isCheckmate(const PieceColor& colorInCheckmate, const std::optional<Board>& board) const;
            bool isEnPassantPosition(uint8_t x, uint8_t y) const;
        public:

        private:
            Board board;
            // std::vector<ChessMove> posibleMoves;
            std::optional<ChessboardPosition> enPassantPosition;
            std::optional<ChessboardPosition> selectedPieceSquere;
            PieceColor turn;
    };
}