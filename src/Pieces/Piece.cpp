#include "Piece.hpp"
#include "../Board.hpp"

Chess::Piece::Piece(const PieceColor color, const PieceType type, Board& board, const ChessboardPosition& position):
    color(color),
    type(type),
    board(board),
    position(position)
{
}
