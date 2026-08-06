#include "Queen.hpp"
#include "../Board.hpp"
#include "../UniversalVector.hpp"
#include"../ChessMove.hpp"

Chess::Queen::Queen(const PieceColor color, const Board &board, const ChessboardPosition &position):
    Piece::Piece(color, PieceType::QUEEN, board, position)
{
}

std::unique_ptr<Chess::Piece> Chess::Queen::clone() const
{
    return std::make_unique<Queen>(*this);
}

std::vector<Chess::ChessMove> Chess::Queen::getPseudoPossibleMoves() const
{
    return getMovesBasedOfDirs(combinedDirs);
}
