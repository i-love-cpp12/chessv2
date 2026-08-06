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
    return getMovesBasedOfOffsets(offsets);
}

void Chess::King::setPosition(const ChessboardPosition &dest)
{
    position = dest;
    _hasMoved = true;
}
