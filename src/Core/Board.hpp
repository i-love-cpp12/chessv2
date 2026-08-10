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
#include<map>

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

            void removePiece(int8_t x, int8_t y);
            void removePiece(const UniversalVector<int8_t>& pos);

            void setPiece(int8_t x, int8_t y, PieceType type, PieceColor color);
            void setPiece(ChessboardPosition position, PieceType type, PieceColor color);
            void setPiece(const UniversalVector<int8_t>& position, PieceType type, PieceColor color);

            void movePiece(const ChessboardPosition& from, const ChessboardPosition& to);
        private:
            void generateBoard(const std::string& boardSetupFilePath);
            static constexpr PieceType charToPieceType(char type);
            std::unique_ptr<Piece> pieceFactory(PieceType type, PieceColor color, const ChessboardPosition &position) const;
            std::unique_ptr<Piece> pieceFactory(char charType, const ChessboardPosition& position) const;
        public:
            static constexpr int8_t WIDTH = 8;
            static constexpr int8_t HEIGHT = 8;
        private:
            std::array<std::unique_ptr<Piece>, WIDTH * HEIGHT> data;
            const Piece* whiteKing;
            const Piece* blackKing;
    };
}
