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
