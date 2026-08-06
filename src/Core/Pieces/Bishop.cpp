#include "Bishop.hpp"
#include "../Board.hpp"
#include "../UniversalVector.hpp"
#include"../ChessMove.hpp"

Chess::Bishop::Bishop(const PieceColor color, const Board &board, const ChessboardPosition &position):
    Piece::Piece(color, PieceType::BISHOP, board, position)
{
}

std::unique_ptr<Chess::Piece> Chess::Bishop::clone() const
{
    return std::make_unique<Bishop>(*this);
}

std::vector<Chess::ChessMove> Chess::Bishop::getPseudoPossibleMoves() const
{
    return getMovesBasedOfDirs(diagonalDirs);
}
