#pragma once
#include<cstdint>
#include<string>
#include<string_view>
#include"UniversalVector.hpp"

namespace Chess
{
    class ChessboardPosition
    {
        public:
            ChessboardPosition(uint8_t x, uint8_t y);
            ChessboardPosition(const UniversalVector<uint8_t>& pos);
            ChessboardPosition(const std::string& chessNotationPosition);

            uint8_t getX() const {return x;}
            uint8_t getY() const {return y;}
            std::string getChessNotationPosition();

            void setPosition(uint8_t x, uint8_t y);
            void setPosition(const UniversalVector<uint8_t>& pos);
            void setPosition(const std::string& chessNotationPosition);

        private:
            static constexpr std::string_view colsCharsChessNotation = "ABCDEFGH";
            static constexpr std::string_view rowsCharsChessNotation = "87654321";

            uint8_t x;
            uint8_t y;
    };
}