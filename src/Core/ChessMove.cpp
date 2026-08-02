#include "ChessMove.hpp"

Chess::ChessMove::ChessMove(const ChessboardPosition& source, const ChessboardPosition& destination, const ChessMoveType moveType, const std::optional<PieceType>& capturedPieceType):
    source(source),
    destination(destination),
    moveType(moveType),
    capturedPieceType(capturedPieceType)
{
}
