#include "King.hpp"
#include "../Board.hpp"
#include "../UniversalVector.hpp"
#include"../ChessMove.hpp"

Chess::King::King(const PieceColor color, const Board* board, const ChessboardPosition &position):
    Piece::Piece(color, PieceType::KING, board, position), _hasMoved(false)
{
}

std::unique_ptr<Chess::Piece> Chess::King::clone(const Board* newBoard) const
{
    std::unique_ptr<Chess::Piece> cloned = std::make_unique<King>(*this);
    if(newBoard)
        cloned->bindBoard(newBoard);
    return cloned;
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
