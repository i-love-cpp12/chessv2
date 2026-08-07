#pragma once

#include<cstdint>
#include<array>
#include<memory>
#include<string>
#include<optional>
#include"Pieces/Piece.hpp"
#include"ChessboardPosition.hpp"
#include"UniversalVector.hpp"
#include<functional>

namespace Chess
{
    class Board
    {
        public:
            Board(const std::string& boardSetupFilePath = "../config/chessboardSetup.json");
            Board(const Board& other);
            static bool inBoardBounds(int8_t x, int8_t y);
            static bool inBoardBounds(const UniversalVector<int8_t>& pos);

            void foreachSquare(std::function<bool(const Piece*)> callback) const;

            const Piece* getPiece(int8_t x, int8_t y) const;
            const Piece* getPiece(const UniversalVector<int8_t>& pos) const;
            const Piece* getPiece(const ChessboardPosition& pos) const;

            const Piece& getKing(const PieceColor color) const;

            const void removePiece(int8_t x, int8_t y);
            const void removePiece(const UniversalVector<int8_t>& pos);

            void movePiece(const ChessboardPosition& from, const ChessboardPosition& to);
        private:
            void generateBoard(const std::string& boardSetupFilePath);
            std::unique_ptr<Piece> pieceFactory(char type, const ChessboardPosition& position) const;
        public:
            static constexpr int8_t WIDTH = 8;
            static constexpr int8_t HEIGHT = 8;
        private:
            std::array<std::unique_ptr<Piece>, WIDTH * HEIGHT> data;
            const Piece* whiteKing;
            const Piece* blackKing;
    };
}
