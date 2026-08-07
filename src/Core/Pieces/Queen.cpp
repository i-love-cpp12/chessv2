#include "Queen.hpp"
#include "../Board.hpp"
#include "../UniversalVector.hpp"
#include"../ChessMove.hpp"

Chess::Queen::Queen(const PieceColor color, const Board* board, const ChessboardPosition &position):
    Piece::Piece(color, PieceType::QUEEN, board, position)
{
}

std::unique_ptr<Chess::Piece> Chess::Queen::clone(const Board* newBoard) const
{
    std::unique_ptr<Chess::Piece> cloned = std::make_unique<Queen>(*this);
    if(newBoard)
        cloned->bindBoard(newBoard);
    return cloned;
}

std::vector<Chess::ChessMove> Chess::Queen::getPseudoPossibleMoves() const
{
    return getMovesBasedOfDirs(combinedDirs);
}
