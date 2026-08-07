#include "Game.hpp"
#include<cmath>

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

    enPassantPosition = move.moveType & ChessMoveType::DOUBLE_FORWARD ? std::optional<ChessboardPosition>(move.destination) : std::nullopt;

    if(move.moveType & ChessMoveType::EN_PASSANT)
        board.removePiece(move.destination.getX(), move.source.getY());

    turn = turn == PieceColor::CHESS_WHITE ? PieceColor::CHESS_BLACK : PieceColor::CHESS_WHITE;

    selectedPieceSquere.reset();
}

std::vector<Chess::ChessMove> Chess::Game::getPossibleMovesFor(const Piece *piece) const
{
    if(!piece)
        return {};

    std::vector<Chess::ChessMove> possibleMoves = piece->getPseudoPossibleMoves();

    addPossibleMovesEnPassant(piece, possibleMoves);


    for(size_t i = 0; i < possibleMoves.size(); ++i)
    {
        const Chess::ChessMove& move = possibleMoves[i];
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

std::vector<Chess::ChessMove> Chess::Game::getPossibleMovesFor(const ChessboardPosition &position) const
{
    return getPossibleMovesFor(board.getPiece(position.getX(), position.getY()));
}

bool Chess::Game::isSquareAttacked(const ChessboardPosition& square, const PieceColor& colorUnderAttack, const Board& board) const
{
    //no deep copy on board in piece class use ptr and setboard or smth
    for(int8_t y = 0; y < board.HEIGHT; ++y)
    {
        for(int8_t x = 0; x < board.WIDTH; ++x)
        {
            const Piece* const piece = board.getPiece(x, y);
            if(!piece || piece->color == colorUnderAttack)
                continue;
            for(const auto& move : piece->getPseudoPossibleMoves())
            {
                if(move.destination == square)
                    return true;
            }
        }
    }
    return false;
}

bool Chess::Game::isCheck(const PieceColor &colorInCheck, const Board& board) const
{
    ChessboardPosition kingPos = board.getKing(colorInCheck).getPosition();
    return isSquareAttacked(kingPos, colorInCheck, board);
}

bool Chess::Game::isCheckmate(const PieceColor &colorInCheckmate, const Board& board) const
{
    return false;
}

bool Chess::Game::isEnPassantPosition(const UniversalVector<int8_t>& position) const
{
    return enPassantPosition && enPassantPosition->getX() == position.x && enPassantPosition->getY() == position.y;
}

std::vector<Chess::ChessMove> Chess::Game::addPossibleMovesEnPassant(const Piece *piece, std::vector<ChessMove>& possibleMoves) const
{
    if(!piece->type == PieceType::PAWN)
        return {};

    const int8_t dir = piece->color == PieceColor::CHESS_WHITE ? -1 : 1;

    //en passant left check
    UniversalVector<int8_t> left = {(int8_t)(piece->getPosition().getX() + 1), piece->getPosition().getY()};
    if(isEnPassantPosition(left))
        possibleMoves.emplace_back(piece->getPosition(), ChessboardPosition(left.x, left.y + dir), ChessMoveType::CAPTURE | ChessMoveType::EN_PASSANT, PieceType::PAWN);

    //en passant right check
    UniversalVector<int8_t> right = {(int8_t)(piece->getPosition().getX() - 1), piece->getPosition().getY()};
    if(isEnPassantPosition(right))
        possibleMoves.emplace_back(piece->getPosition(), ChessboardPosition(right.x, right.y + dir), ChessMoveType::CAPTURE | ChessMoveType::EN_PASSANT, PieceType::PAWN);

    return possibleMoves;
}
