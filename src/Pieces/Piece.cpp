#include "Piece.hpp"
#include "../Board.hpp"

Chess::Piece::Piece(const PieceColor color, const PieceType type, const Board& board, const ChessboardPosition& position):
    color(color),
    type(type),
    board(board),
    position(position)
{
}

void Chess::Piece::setPosition(const ChessboardPosition &dest)
{
    position = dest;
}
