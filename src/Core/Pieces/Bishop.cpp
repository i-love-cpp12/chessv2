#include "Bishop.hpp"
#include "../Board.hpp"
#include "../UniversalVector.hpp"
#include"../ChessMove.hpp"

Chess::Bishop::Bishop(const PieceColor color, const Board* board, const ChessboardPosition &position):
    Piece::Piece(color, PieceType::BISHOP, board, position)
{
}

std::unique_ptr<Chess::Piece> Chess::Bishop::clone(const Board* newBoard) const
{
    std::unique_ptr<Chess::Piece> cloned = std::make_unique<Bishop>(*this);
    if(newBoard)
        cloned->bindBoard(newBoard);
    return cloned;
}

std::vector<Chess::ChessMove> Chess::Bishop::getPseudoPossibleMoves() const
{
    return getMovesBasedOfDirs(diagonalDirs);
}
