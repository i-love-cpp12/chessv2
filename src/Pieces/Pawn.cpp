#include "Pawn.hpp"
#include "../Board.hpp"

Chess::Pawn::Pawn(const PieceColor color, const PieceType type, const Board &board, const ChessboardPosition &position):
    Piece::Piece(color, type, board, position)
{
}

std::vector<Chess::ChessMove> Chess::Pawn::possbileMoves() const
{
    // uint8_t x = position.getX();
    // uint8_t y = position.getY();
    // std::vector<Chess::ChessMove> result;
    // result.reserve(4);

    // if(board.inBoardBounds(x, y - 1) && !board.getPiece(x, y - 1))
    // {
    //     result.emplace_back(ChessboardPosition(x, y - 1), ())
    // }
    return std::vector<Chess::ChessMove>();
}

void Chess::Pawn::setPosition(const ChessboardPosition &dest)
{
    position = dest;
    hasMoved = true;
}
