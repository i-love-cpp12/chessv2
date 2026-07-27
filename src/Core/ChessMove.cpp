#include "ChessMove.hpp"

Chess::ChessMove::ChessMove(const ChessboardPosition& destination, const Piece& piece, const ChessMoveType moveType, const std::optional<PieceType>& capturedPieceType):
    destination(destination),
    piece(piece),
    source(piece.getPosition()),
    moveType(moveType),
    capturedPieceType(capturedPieceType)
{
}
