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
    std::optional<Chess::ChessboardPosition> selectedSquare = game.getSelectedSquere();
    renderBoard();
    renderSelectedSquare(selectedSquare);
    renderPieces(game.getBoard());
    renderSuggestedMoves(selectedSquare ? game.getPossibleMovesFor(selectedSquare->getX(), selectedSquare->getY()) : std::vector<Chess::ChessMove>{});
}

void Chess::Renderer::renderBoard() const
{
    DrawTexturePro(textureManager.getTexture(), textureManager.getSprite("board"), boardRect, {0, 0}, 0.0f, WHITE);
}

void Chess::Renderer::renderPieces(const Chess::Board &board) const
{
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
    Rectangle dest = chessPositionToDisplayPos(piece->getPosition());
    DrawTexturePro(textureManager.getTexture(), sprite, dest, {0, 0}, 0.0f, WHITE);
}

void Chess::Renderer::renderSelectedSquare(const std::optional<ChessboardPosition> &selectedSquare) const
{
    if(selectedSquare)
        DrawRectangleRec(chessPositionToDisplayPos(selectedSquare.value()), Color{118, 161, 18, 150});
}

void Chess::Renderer::renderSuggestedMoves(const std::vector<Chess::ChessMove>& posibleMoves) const
{
    for(const auto& move : posibleMoves)
    {
        Vector2 center = {move.destination.getX() * (float)CELL_SIZE + CELL_SIZE / 2.0f, move.destination.getY() * (float)CELL_SIZE + CELL_SIZE / 2.0f};
        const int fullRadius = CELL_SIZE / 2;
        Color color = {75, 75, 75, 130};

        if(move.moveType & Chess::ChessMoveType::CAPTURE)
            DrawRing(center, fullRadius * 0.85f , fullRadius * 0.97f, 0.0f, 360.0f, 35, color);
        else
            DrawRing(center, 0.0f , fullRadius * 0.3, 0.0f, 360.0f, 35, color);
    }
}

Rectangle Chess::Renderer::getPieceSprite(const PieceColor& color, const PieceType& type) const
{
    return textureManager.getSprite(pieceTypeToSpriteKey.at({color, type}));
}

Rectangle Chess::Renderer::chessPositionToDisplayPos(const Chess::ChessboardPosition &position) const
{
    return {
        position.getX() * (float)CELL_SIZE,
        position.getY() * (float)CELL_SIZE,
        (float)CELL_SIZE,
        (float)CELL_SIZE
    };
}
