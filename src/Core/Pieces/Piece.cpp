#include "Piece.hpp"
#include "../Board.hpp"
#include "../ChessMove.hpp"

Chess::Piece::Piece(const PieceColor color, const PieceType type, const Board& board, const ChessboardPosition& position):
    color(color),
    type(type),
    board(board),
    position(position)
{
}

void Chess::Piece::setPosition(const ChessboardPosition& dest)
{
    position = dest;
}

std::vector<Chess::ChessMove> Chess::Piece::getMovesBasedOfDirs(const std::span<const UniversalVector<int8_t>> dirs) const
{
    std::vector<Chess::ChessMove> result;
    result.reserve(dirs.size() * 7);
    for(const auto& dir : dirs)
    {
        UniversalVector<int8_t> currPosition = {(int8_t)(position.getX() + dir.x), (int8_t)(position.getY() + dir.y)};

        while(board.inBoardBounds(currPosition))
        {
            const Piece* targetPiece = board.getPiece(currPosition);

            if(targetPiece)
            {
                if(targetPiece->color != color)
                    result.emplace_back(
                        position,
                        currPosition,
                        Chess::ChessMoveType::NONE | Chess::ChessMoveType::CAPTURE,
                        std::optional<Chess::PieceType>(targetPiece->type)
                    );
                break;
            }
            result.emplace_back(position, currPosition);
            currPosition = {(int8_t)(currPosition.x + dir.x), (int8_t)(currPosition.y + dir.y)};
        }
    }
    return result;
}

std::vector<Chess::ChessMove> Chess::Piece::getMovesBasedOfOffsets(const std::span<const UniversalVector<int8_t>> offsets) const
{
    int8_t x = position.getX();
    int8_t y = position.getY();
    std::vector<ChessMove> result;
    result.reserve(8);
    for(const auto& dir : offsets)
    {
        UniversalVector<int8_t> targetPos = {(int8_t)(x + dir.x), (int8_t)(y + dir.y)};
        if(!board.inBoardBounds(targetPos))
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
