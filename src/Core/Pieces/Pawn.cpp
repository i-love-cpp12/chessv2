#include "Pawn.hpp"
#include "../Board.hpp"
#include "../UniversalVector.hpp"
#include"../ChessMove.hpp"

Chess::Pawn::Pawn(const PieceColor color, const Board &board, const ChessboardPosition &position):
    Piece::Piece(color, PieceType::PAWN, board, position)
{
}

std::unique_ptr<Chess::Piece> Chess::Pawn::clone() const
{
    return std::make_unique<Pawn>(*this);
}

std::vector<Chess::ChessMove> Chess::Pawn::getPseudoPossibleMoves() const
{
    int8_t dir = color == PieceColor::CHESS_WHITE ? -1 : 1;

    int8_t x = position.getX();
    int8_t y = position.getY();
    std::vector<ChessMove> result;
    result.reserve(4);

    UniversalVector<int8_t> forward{x, (int8_t)(y + dir)};
    //forward
    if(board.inBoardBounds(forward) && !board.getPiece(forward))
    {
        result.emplace_back(position, ChessboardPosition(forward), (isPromoting(forward) ? ChessMoveType::PROMOTION : ChessMoveType::NONE));
        UniversalVector<int8_t> doubleForward{x, (int8_t)(y + dir * 2)};
        //double forward
        if(board.inBoardBounds(doubleForward) && !board.getPiece(doubleForward) && !hasMoved())
            result.emplace_back(position, ChessboardPosition(doubleForward), (isPromoting(doubleForward) ? ChessMoveType::PROMOTION : ChessMoveType::NONE));
    }

    UniversalVector<int8_t> leftCapture{(int8_t)(x - 1), (int8_t)(y + dir)};
    //left capture
    if(board.inBoardBounds(leftCapture) && board.getPiece(leftCapture) && board.getPiece(leftCapture)->color != color)
    {
        result.emplace_back(
            position,
            ChessboardPosition(leftCapture),
            ChessMoveType::CAPTURE | (isPromoting(leftCapture) ? ChessMoveType::PROMOTION : ChessMoveType::NONE),
            board.getPiece(leftCapture)->type
        );
    }

    UniversalVector<int8_t> rightCapture{(int8_t)(x + 1), (int8_t)(y + dir)};
    //right capture
    if(board.inBoardBounds(rightCapture) && board.getPiece(rightCapture) && board.getPiece(rightCapture)->color != color)
    {
        result.emplace_back(
            position,
            ChessboardPosition(rightCapture),
            ChessMoveType::CAPTURE | (isPromoting(rightCapture) ? ChessMoveType::PROMOTION : ChessMoveType::NONE),
            board.getPiece(rightCapture)->type
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
