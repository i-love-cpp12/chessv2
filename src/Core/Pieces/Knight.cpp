#include "Knight.hpp"
#include "../Board.hpp"
#include "../UniversalVector.hpp"
#include"../ChessMove.hpp"

Chess::Knight::Knight(const PieceColor color, const Board* board, const ChessboardPosition &position):
    Piece::Piece(color, PieceType::KNIGHT, board, position)
{
}

std::unique_ptr<Chess::Piece> Chess::Knight::clone(const Board* newBoard) const
{
    std::unique_ptr<Chess::Piece> cloned = std::make_unique<Knight>(*this);
    if(newBoard)
        cloned->bindBoard(newBoard);
    return cloned;
}

std::vector<Chess::ChessMove> Chess::Knight::getPseudoPossibleMoves() const
{
    return getMovesBasedOfOffsets(offsets);
}
