#include "Piece.hpp"
#include "../Board.hpp"

Chess::Piece::Piece(const PieceColor color, const PieceType type, Board& board, const uint8_t x, const uint8_t y):
    color(color),
    type(type),
    board(board),
    x(x),
    y(y)
{
}
