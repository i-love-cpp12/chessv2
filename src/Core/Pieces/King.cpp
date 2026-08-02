#include "King.hpp"
#include "../Board.hpp"
#include "../UniversalVector.hpp"
#include"../ChessMove.hpp"

Chess::King::King(const PieceColor color, const Board &board, const ChessboardPosition &position):
    Piece::Piece(color, PieceType::KING, board, position)
{
}

std::unique_ptr<Chess::Piece> Chess::King::clone() const
{
    return std::make_unique<King>(*this);
}

std::vector<Chess::ChessMove> Chess::King::getPseudoPossibleMoves() const
{
    uint8_t x = position.getX();
    uint8_t y = position.getY();
    std::vector<ChessMove> result;
    result.reserve(8);
    for(const auto& dir : offsets)
    {
        UniversalVector<uint8_t> targetPos = {(uint8_t)(x + dir.x), (uint8_t)(y + dir.y)};
        if(!board.inBoardBounds(x + dir.x, y + dir.y))
            continue;
        const Piece* targetPiece = board.getPiece(targetPos);

        Chess::ChessMoveType moveType = Chess::ChessMoveType::NONE;
        std::optional<Chess::PieceType> capturedPieceType = std::nullopt;

        if(targetPiece)
        {
            if(targetPiece->color == color)
                continue;
            moveType = moveType | Chess::ChessMoveType::CAPTURE;
            capturedPieceType = std::optional<Chess::PieceType>(targetPiece->type);
        }

        result.emplace_back(position, targetPos, moveType, capturedPieceType);
    }
    return result;
}

void Chess::King::setPosition(const ChessboardPosition &dest)
{
    position = dest;
    _hasMoved = true;
}
