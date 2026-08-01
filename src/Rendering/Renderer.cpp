#include "Renderer.hpp"
#include "../Core/ChessboardPosition.hpp"
const std::map<Chess::SpritePieceKey, std::string> Chess::Renderer::pieceTypeToSpriteKey = 
{
    {{PieceColor::CHESS_WHITE, PieceType::KING},   "white_king"},
    {{PieceColor::CHESS_WHITE, PieceType::QUEEN},  "white_queen"},
    {{PieceColor::CHESS_WHITE, PieceType::ROOK},   "white_rook"},
    {{PieceColor::CHESS_WHITE, PieceType::BISHOP}, "white_bishop"},
    {{PieceColor::CHESS_WHITE, PieceType::KNIGHT}, "white_knight"},
    {{PieceColor::CHESS_WHITE, PieceType::PAWN},   "white_pawn"},

    {{PieceColor::CHESS_BLACK, PieceType::KING},   "black_king"},
    {{PieceColor::CHESS_BLACK, PieceType::QUEEN},  "black_queen"},
    {{PieceColor::CHESS_BLACK, PieceType::ROOK},   "black_rook"},
    {{PieceColor::CHESS_BLACK, PieceType::BISHOP}, "black_bishop"},
    {{PieceColor::CHESS_BLACK, PieceType::KNIGHT}, "black_knight"},
    {{PieceColor::CHESS_BLACK, PieceType::PAWN},   "black_pawn"}
};

Chess::Renderer::Renderer(const std::string& texturePath, const std::string& JSONCoordsPath): boardRect({0, 0, 800, 800}), CELL_SIZE(boardRect.width / 8)
{
    InitWindow(800, 800, "chess2");
    SetTargetFPS(30);
    textureManager = TextureManager(texturePath, JSONCoordsPath);
}

void Chess::Renderer::renderGame(const Chess::Game &game) const
{
    renderBoard(game.getBoard());
}

void Chess::Renderer::renderBoard(const Chess::Board &board) const
{
    //draw board texture
    DrawTexturePro(textureManager.getTexture(), textureManager.getSprite("board"), boardRect, {0, 0}, 0.0f, WHITE);
    for(uint8_t y = 0; y < board.HEIGHT; ++y)
    {
        for(uint8_t x = 0; x < board.WIDTH; ++x)
        {
            renderPiece(board.getPiece(x, y));
        }
    }
}

void Chess::Renderer::renderPiece(const Piece *const piece) const
{
    if(!piece)
        return;
    Rectangle sprite = getPieceSprite(piece->color, piece->type);
    Rectangle dest = {piece->getPosition().getX() * CELL_SIZE, piece->getPosition().getY() * CELL_SIZE, CELL_SIZE, CELL_SIZE};
    DrawTexturePro(textureManager.getTexture(), sprite, dest, {0, 0}, 0.0f, WHITE);
}

Rectangle Chess::Renderer::getPieceSprite(const PieceColor& color, const PieceType& type) const
{
    return textureManager.getSprite(pieceTypeToSpriteKey.at({color, type}));
}
