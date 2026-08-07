#pragma once
#include<raylib.h>
#include"../Core/Game.hpp"
#include"../Core/Board.hpp"
#include"TextureManager.hpp"
#include"../Core/Pieces/Piece.hpp"
#include"../Core/ChessMove.hpp"
#include<map>
#include<tuple>

namespace Chess
{
    struct SpritePieceKey
    {
        PieceColor color;
        PieceType type;

        bool operator<(const SpritePieceKey& other) const
        {
            return std::tie(color, type) < std::tie(other.color, other.type);
        }
    };

    class Renderer
    {
        public:
            Renderer(const std::string& texturePath, const std::string& JSONCoordsPath);
            void renderGame(const Chess::Game& game) const;
        private:
            void renderBoard() const;
            void renderPieces(const Chess::Board& board) const;
            void renderPiece(const Piece* const piece) const;
            void renderSelectedSquare(const std::optional<ChessboardPosition>& selectedSquare) const;
            void renderSuggestedMoves(const std::vector<Chess::ChessMove>& posibleMoves) const;
            void renderGameStatus(const GameStatusForWhite& status) const;
            Rectangle getPieceSprite(const PieceColor& color, const PieceType& type) const;
            Rectangle chessPositionToDisplayPos(const Chess::ChessboardPosition& position) const;
        private:
            Chess::TextureManager textureManager;
            static const std::map<SpritePieceKey, std::string> pieceTypeToSpriteKey;
            const Rectangle boardRect;
            const unsigned int CELL_SIZE;
    };
}