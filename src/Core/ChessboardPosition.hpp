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
            ChessboardPosition(int8_t x, int8_t y);
            ChessboardPosition(const UniversalVector<int8_t>& pos);
            ChessboardPosition(const std::string& chessNotationPosition);

            bool operator==(const ChessboardPosition& other) const;

            int8_t getX() const {return x;}
            int8_t getY() const {return y;}
            UniversalVector<int8_t> getUniversalVector(){ return {x, y}; }
            std::string getChessNotationPosition();

            void setPosition(int8_t x, int8_t y);
            void setPosition(const UniversalVector<int8_t>& pos);
            void setPosition(const std::string& chessNotationPosition);

        private:
            static constexpr std::string_view colsCharsChessNotation = "ABCDEFGH";
            static constexpr std::string_view rowsCharsChessNotation = "87654321";

            int8_t x;
            int8_t y;
    };
}