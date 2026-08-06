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
            void onSquereSelected(int8_t x, int8_t y);
            const Board& getBoard() const { return board; }

            //get filtered pseudo moves
            std::vector<ChessMove> getPossibleMovesFor(const Piece* piece) const;
            std::vector<ChessMove> getPossibleMovesFor(const ChessboardPosition& position) const;

        private:
            void makeMove(const ChessMove& move);
            bool isSquareAttacked(const ChessboardPosition& square, const PieceColor& colorUnderAttack, const std::optional<Board>& board) const;
            bool isCheck(const PieceColor& colorInCheck, const std::optional<Board>& board) const;
            bool isCheckmate(const PieceColor& colorInCheckmate, const std::optional<Board>& board) const;
            bool isEnPassantPosition(const UniversalVector<int8_t>& position) const;
            std::vector<ChessMove> addPossibleMovesEnPassant(const Piece* piece, std::vector<ChessMove>& possibleMoves) const;
        public:

        private:
            Board board;
            // std::vector<ChessMove> posibleMoves;
            std::optional<ChessboardPosition> enPassantPosition;
            std::optional<ChessboardPosition> selectedPieceSquere;
            const Piece* whiteKing;
            const Piece* blackKing;
            PieceColor turn;
    };
}