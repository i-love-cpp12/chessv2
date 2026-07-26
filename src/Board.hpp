#pragma once

#include<cstdint>
#include<array>
#include<memory>
#include<string>
#include"Pieces/Piece.hpp"
#include"ChessboardPosition.hpp"

namespace Chess
{
    struct PieceMove
    {
        ChessboardPosition from;
        ChessboardPosition to;
    };

    class Board
    {
        public:
            static bool inBoardBounds(uint8_t x, uint8_t y);
        // private:
        public:
            void generateBoard(const std::string& boardSetupFilePath = "../config/chessboardSetup.json");
        public:
            static constexpr uint8_t WIDTH = 8;
            static constexpr uint8_t HEIGHT = 8;
        private:
            std::array<std::unique_ptr<Piece>, WIDTH * HEIGHT> data;
    };
}
