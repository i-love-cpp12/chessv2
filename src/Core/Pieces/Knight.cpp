#include "Knight.hpp"
#include "../Board.hpp"
#include "../UniversalVector.hpp"
#include"../ChessMove.hpp"

Chess::Knight::Knight(const PieceColor color, const Board &board, const ChessboardPosition &position):
    Piece::Piece(color, PieceType::KNIGHT, board, position)
{
}

std::unique_ptr<Chess::Piece> Chess::Knight::clone() const
{
    return std::make_unique<Knight>(*this);
}

std::vector<Chess::ChessMove> Chess::Knight::getPseudoPossibleMoves() const
{
    return getMovesBasedOfOffsets(offsets);
}
