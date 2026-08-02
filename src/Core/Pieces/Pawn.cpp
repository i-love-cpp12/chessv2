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

    uint8_t x = position.getX();
    uint8_t y = position.getY();
    std::vector<ChessMove> result;
    result.reserve(4);

    UniversalVector<uint8_t> forward{x, (uint8_t)(y + dir)};
    //forward
    if(board.inBoardBounds(x, y + dir) && !board.getPiece(forward))
    {
        result.emplace_back(position, ChessboardPosition(forward), (isPromoting(forward) ? ChessMoveType::PROMOTION : ChessMoveType::NONE));
        UniversalVector<uint8_t> doubleForward{x, (uint8_t)(y + dir * 2)};
        //double forward
        if(board.inBoardBounds(x, y + dir * 2) && !board.getPiece(doubleForward) && !hasMoved())
            result.emplace_back(position, ChessboardPosition(doubleForward), (isPromoting(doubleForward) ? ChessMoveType::PROMOTION : ChessMoveType::NONE));
    }

    UniversalVector<uint8_t> leftCapture{(uint8_t)(x - 1), (uint8_t)(y + dir)};
    //left capture
    if(board.inBoardBounds(x - 1, y + dir) && board.getPiece(leftCapture) && board.getPiece(leftCapture)->color != color)
    {
        result.emplace_back(
            position,
            ChessboardPosition(leftCapture),
            ChessMoveType::CAPTURE | (isPromoting(leftCapture) ? ChessMoveType::PROMOTION : ChessMoveType::NONE),
            board.getPiece(leftCapture)->type
        );
    }

    UniversalVector<uint8_t> rightCapture{(uint8_t)(x + 1), (uint8_t)(y + dir)};
    //right capture
    if(board.inBoardBounds(x + 1, y + dir) && board.getPiece(rightCapture) && board.getPiece(rightCapture)->color != color)
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
