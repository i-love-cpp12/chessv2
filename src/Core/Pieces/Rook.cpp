#include "Rook.hpp"
#include "../Board.hpp"
#include "../UniversalVector.hpp"
#include"../ChessMove.hpp"

Chess::Rook::Rook(const PieceColor color, const Board* board, const ChessboardPosition &position):
    Piece::Piece(color, PieceType::ROOK, board, position), _hasMoved(false)
{
}

std::unique_ptr<Chess::Piece> Chess::Rook::clone(const Board* newBoard) const
{
    std::unique_ptr<Chess::Piece> cloned = std::make_unique<Rook>(*this);
    if(newBoard)
        cloned->bindBoard(newBoard);
    return cloned;
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
