#include "Game.hpp"


Chess::Game::Game()/*: posibleMoves({
    Chess::ChessMove(Chess::ChessboardPosition(0, 0), *board.getPiece(0, 1)),
    Chess::ChessMove(Chess::ChessboardPosition(0, 1), *board.getPiece(0, 1), Chess::ChessMoveType::CAPTURE)}
)*/
// :selectedPieceSquere(std::optional<Chess::ChessboardPosition>(Chess::ChessboardPosition(1, 1)))
{
}

void Chess::Game::onSquereSelected(int8_t x, int8_t y)
{
    if(!board.inBoardBounds(x, y))
        return;
    
    const Piece* const targetPiece = board.getPiece(x, y);

    if(targetPiece && targetPiece->color == turn)
    {
        selectedPieceSquere = targetPiece->getPosition();
        return;
    }

    if(!selectedPieceSquere)
        return;

    std::vector<Chess::ChessMove> possibleMoves = getPossibleMovesFor(selectedPieceSquere.value());
    Chess::ChessboardPosition targetPosition(x, y);
    for(size_t i = 0; i < possibleMoves.size(); ++i)
    {
        if(possibleMoves[i].destination == targetPosition)
        {
            makeMove(possibleMoves[i]);
            break;
        }
    }
    selectedPieceSquere.reset();
}

void Chess::Game::makeMove(const ChessMove &move)
{
    board.movePiece(move.source, move.destination);

    turn = turn == PieceColor::CHESS_WHITE ? PieceColor::CHESS_BLACK : PieceColor::CHESS_WHITE;

    selectedPieceSquere.reset();
}

std::vector<Chess::ChessMove> Chess::Game::getPossibleMovesFor(const Piece *piece) const
{
    if(!piece)
        return {};

    std::vector<Chess::ChessMove> possibleMoves = piece->getPseudoPossibleMoves();

    for(size_t i = 0; i < possibleMoves.size(); ++i)
    {
        Chess::ChessMove move = possibleMoves[i];
        Board boardCopy = board;
        
        boardCopy.movePiece(move.source, move.destination);

        if(isCheck(piece->color, boardCopy))
        {
            possibleMoves.erase(possibleMoves.begin() + i);
            --i;
            continue;
        }
    }

    return possibleMoves;
}

std::vector<Chess::ChessMove> Chess::Game::getPossibleMovesFor(int8_t x, int8_t y) const
{
    return getPossibleMovesFor(board.getPiece(x, y));
}

std::vector<Chess::ChessMove> Chess::Game::getPossibleMovesFor(const UniversalVector<int8_t>& position) const
{
    return getPossibleMovesFor(board.getPiece(position.x, position.y));
}

std::vector<Chess::ChessMove> Chess::Game::getPossibleMovesFor(const ChessboardPosition &position) const
{
    return getPossibleMovesFor(board.getPiece(position.getX(), position.getY()));
}

bool Chess::Game::isCheck(const PieceColor &colorInCheck, const std::optional<Board> &board) const
{
    return false;
}

bool Chess::Game::isCheckmate(const PieceColor &colorInCheckmate, const std::optional<Board> &board) const
{
    return false;
}

bool Chess::Game::isEnPassantPosition(int8_t x, int8_t y) const
{
    return enPassantPosition && enPassantPosition->getX() == x && enPassantPosition->getY() == y;
}