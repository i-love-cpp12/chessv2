#include "Pawn.hpp"
#include "../Board.hpp"
#include "../UniversalVector.hpp"

Chess::Pawn::Pawn(const PieceColor color, const PieceType type, const Board &board, const ChessboardPosition &position):
    Piece::Piece(color, type, board, position)
{
}

std::vector<Chess::ChessMove> Chess::Pawn::getPseudoPossibleMoves() const
{
    int8_t dir = color == PieceColor::CHESS_WHITE ? -1 : 1;

    uint8_t x = position.getX();
    uint8_t y = position.getY();
    std::vector<Chess::ChessMove> result;
    result.reserve(4);

    UniversalVector<uint8_t> forward(x, y + dir);
    //forward
    if(board.inBoardBounds(forward) && !board.getPiece(forward))
    {
        result.emplace_back(ChessboardPosition(forward), *this, (isPromoting(forward) ? ChessMoveType::PROMOTION : ChessMoveType::NONE));
        UniversalVector<uint8_t> doubleForward(x, y + dir * 2);
        //double forward
        if(board.inBoardBounds(doubleForward) && !board.getPiece(doubleForward) && !hasMoved())
            result.emplace_back(ChessboardPosition(doubleForward), *this, (isPromoting(doubleForward) ? ChessMoveType::PROMOTION : ChessMoveType::NONE));
    }

    UniversalVector<uint8_t> leftCapture(x - 1, y + dir);
    //left capture
    if(board.inBoardBounds(leftCapture) && board.getPiece(leftCapture))
    {
        result.emplace_back(
            ChessboardPosition(leftCapture),
            *this,
            ChessMoveType::CAPTURE | (isPromoting(leftCapture) ? ChessMoveType::PROMOTION : ChessMoveType::NONE)
        );
    }

    UniversalVector<uint8_t> rightCapture(x + 1, y + dir);
    //right capture
    if(board.inBoardBounds(rightCapture) && board.getPiece(rightCapture))
    {
        result.emplace_back(
            ChessboardPosition(rightCapture),
            *this,
            ChessMoveType::CAPTURE | (isPromoting(rightCapture) ? ChessMoveType::PROMOTION : ChessMoveType::NONE)
        );
    }
    return result;
}

void Chess::Pawn::setPosition(const ChessboardPosition &dest)
{
    position = dest;
    _hasMoved = true;
}

bool Chess::Pawn::isPromoting(const ChessboardPosition &futurePosition) const
{
    return color == Chess::PieceColor::CHESS_WHITE ? futurePosition.getY() == 0 : futurePosition.getY() == Chess::Board::HEIGHT - 1;
}
