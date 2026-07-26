#pragma once

#include<cstdint>
#include<array>
#include<memory>
#include<string>
#include"Pieces/Piece.hpp"

namespace Chess
{
    struct PieceMove
    {
        uint8_t fromX;
        uint8_t fromY;
        uint8_t toX;
        uint8_t toY;
    };

    class Board
    {
        public:
            static constexpr bool inBoardBounds(uint8_t x, uint8_t y);
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
