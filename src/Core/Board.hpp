#pragma once

#include<cstdint>
#include<array>
#include<memory>
#include<string>
#include<optional>
#include"Pieces/Piece.hpp"
#include"ChessboardPosition.hpp"
#include"UniversalVector.hpp"

namespace Chess
{
    class Board
    {
        public:
            Board(const std::string& boardSetupFilePath = "../config/chessboardSetup.json");
            static bool inBoardBounds(int8_t x, int8_t y);
            static bool inBoardBounds(const UniversalVector<int8_t>& pos);
            const Piece* getPiece(uint8_t x, uint8_t y) const;
            const Piece* getPiece(const UniversalVector<uint8_t>& pos) const;
            void movePiece(const ChessboardPosition& from, const ChessboardPosition& to);
        private:
            void generateBoard(const std::string& boardSetupFilePath);
            std::unique_ptr<Piece> pieceFactory(char type, const ChessboardPosition& position) const;
        public:
            static constexpr uint8_t WIDTH = 8;
            static constexpr uint8_t HEIGHT = 8;
        private:
            std::array<std::unique_ptr<Piece>, WIDTH * HEIGHT> data;
    };
}
