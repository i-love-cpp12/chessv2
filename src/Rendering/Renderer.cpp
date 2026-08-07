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
    Rectangle chessboardSprite = textureManager.getSprite("window_icon");

    Image icon = ImageFromImage(
        LoadImageFromTexture(textureManager.getTexture()),
        chessboardSprite
    );
    
    SetWindowIcon(icon);
}

void Chess::Renderer::renderGame(const Chess::Game &game) const
{
    std::optional<Chess::ChessboardPosition> selectedPieceSquare = game.getSelectedSquere();
    renderBoard();
    renderSelectedSquare(selectedPieceSquare);
    renderPieces(game.getBoard());
    renderSuggestedMoves(selectedPieceSquare ? game.getPossibleMovesFor(selectedPieceSquare.value()) : std::vector<Chess::ChessMove>{});
    renderGameStatus(game.getGameStatus());
}

void Chess::Renderer::renderBoard() const
{
    DrawTexturePro(textureManager.getTexture(), textureManager.getSprite("board"), boardRect, {0, 0}, 0.0f, WHITE);
}

void Chess::Renderer::renderPieces(const Chess::Board &board) const
{
    for(int8_t y = 0; y < board.HEIGHT; ++y)
    {
        for(int8_t x = 0; x < board.WIDTH; ++x)
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

void Chess::Renderer::renderSelectedSquare(const std::optional<ChessboardPosition> &selectedPieceSquare) const
{
    if(selectedPieceSquare)
        DrawRectangleRec(chessPositionToDisplayPos(selectedPieceSquare.value()), Color{118, 161, 18, 150});
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

void Chess::Renderer::renderGameStatus(const GameStatusForWhite& status) const
{
    if(status == GameStatusForWhite::RUNNING)
        return;
    std::string msg;
    switch(status)
    {
        case GameStatusForWhite::WIN :
            msg = "White won!!!";
        break;

        case GameStatusForWhite::LOST :
            msg = "Black won!!!";
        break;

        case GameStatusForWhite::DRAW :
            msg = "Draw!!!";
        break;
    }

    const float popupWidth = boardRect.width / 2.0f; 
    const float popupHeight = boardRect.height / 3.0f;

    DrawRectangleRounded(
        {
            boardRect.width / 2 - popupWidth / 2,
            boardRect.height / 2 - popupHeight / 2,
            popupWidth,
            popupHeight
        },
        0.1f,
        20,
        WHITE
    );
    const int textHeight = 50;
    const int textWidth = MeasureText(msg.c_str(), textHeight);

    DrawText(msg.c_str(), boardRect.width / 2 - textWidth / 2, boardRect.height / 2 - textHeight / 2, textHeight, BLACK);
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
