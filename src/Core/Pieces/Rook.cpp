#include "Rook.hpp"
#include "../Board.hpp"
#include "../UniversalVector.hpp"
#include"../ChessMove.hpp"

Chess::Rook::Rook(const PieceColor color, const Board &board, const ChessboardPosition &position):
    Piece::Piece(color, PieceType::ROOK, board, position)
{
}

std::unique_ptr<Chess::Piece> Chess::Rook::clone() const
{
    return std::make_unique<Rook>(*this);
}

std::vector<Chess::ChessMove> Chess::Rook::getPseudoPossibleMoves() const
{
    return getMovesBasedOfDirs(straightDirs);
}

void Chess::Rook::setPosition(const ChessboardPosition &dest)
{
    position = dest;
    _hasMoved = true;
}
