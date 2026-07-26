#pragma once

#include<cstdint>
#include<array>
#include<memory>
#include<string>
#include<optional>
#include"Pieces/Piece.hpp"
#include"ChessboardPosition.hpp"

namespace Chess
{
    class Board
    {
        public:
            static bool inBoardBounds(uint8_t x, uint8_t y);
            const Piece* getPiece(uint8_t x, uint8_t y) const;
            // bool isEnPassantPosition(uint8_t x, uint8_t y) const;

        private:
            void generateBoard(const std::string& boardSetupFilePath = "../config/chessboardSetup.json");
            Piece* getPieceRef(uint8_t x, uint8_t y) const;

        public:
            static constexpr uint8_t WIDTH = 8;
            static constexpr uint8_t HEIGHT = 8;
        private:
            std::array<std::unique_ptr<Piece>, WIDTH * HEIGHT> data;
            // std::optional<ChessboardPosition> enPassantPosition;
    };
}
