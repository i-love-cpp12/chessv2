#pragma once
#include<cstdint>
#include<string>
#include<algorithm>

namespace Chess
{
    class ChessboardPosition
    {
        public:
            ChessboardPosition(uint8_t x, uint8_t y);
            ChessboardPosition(const std::string& chessNotationPosition);

            uint8_t getX() const {return x;}
            uint8_t getY() const {return y;}
            std::string getChessNotationPosition();

            void setPosition(uint8_t x, uint8_t y);
            void setPosition(const std::string& chessNotationPosition);

        private:
            static constexpr std::string rowsCharsChessNotation;
            static constexpr std::string colsCharsChessNotation;

            uint8_t x;
            uint8_t y;
    };
}