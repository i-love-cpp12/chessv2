#include "Game.hpp"

void Chess::Game::makeMove(const ChessMove &move)
{
    board.movePiece(move.source, move.destination);

    turn = turn == PieceColor::CHESS_WHITE ? PieceColor::CHESS_BLACK : PieceColor::CHESS_WHITE;

    selectedSquere.reset();
}

bool Chess::Game::isEnPassantPosition(uint8_t x, uint8_t y) const
{
    return enPassantPosition && enPassantPosition->getX() == x && enPassantPosition->getY() == y;
}