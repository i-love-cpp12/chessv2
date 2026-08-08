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
    if(!board.inBoardBounds(x, y) || getGameStatus() != GameStatusForWhite::RUNNING)
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

    //set en passant position
    enPassantPosition = move.moveType & ChessMoveType::DOUBLE_FORWARD ? std::optional<ChessboardPosition>(move.destination) : std::nullopt;

    if(move.moveType & ChessMoveType::EN_PASSANT)
        board.removePiece(move.destination.getX(), move.source.getY());

    if(move.moveType & ChessMoveType::SHORT_CASTLE || move.moveType & ChessMoveType::LONG_CASTLE)
    {
        UniversalVector<int8_t> rookPos;
        UniversalVector<int8_t> rookDestination;
        const int8_t y = move.source.getY();

        if(move.moveType & ChessMoveType::SHORT_CASTLE)
        {
            rookPos = UniversalVector<int8_t>(board.WIDTH - 1, y);
            rookDestination = UniversalVector<int8_t>(move.destination.getX() - 1, y);
        }
        else
        {
            rookPos = UniversalVector<int8_t>(0, y);
            rookDestination = UniversalVector<int8_t>(move.destination.getX() + 1, y);
        }

        board.movePiece(ChessboardPosition(rookPos), ChessboardPosition(rookDestination));
    }

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

    addPossibleMovesCastle(piece, possibleMoves);

    return possibleMoves;
}

std::vector<Chess::ChessMove> Chess::Game::getPossibleMovesFor(const ChessboardPosition &position) const
{
    return getPossibleMovesFor(board.getPiece(position.getX(), position.getY()));
}

Chess::GameStatusForWhite Chess::Game::getGameStatus() const
{
    bool hasPosibleMoves = false;

    board.foreachSquare([&](const Piece* piece) -> bool {
        if(piece && piece->color == turn && !getPossibleMovesFor(piece).empty())
        {
            hasPosibleMoves = true;
            return true;
        }
        return false;
    });

    if(hasPosibleMoves)
        return GameStatusForWhite::RUNNING;
    if(!isCheck(turn, board))
        return GameStatusForWhite::DRAW;

    return turn == PieceColor::CHESS_WHITE ? GameStatusForWhite::LOST : GameStatusForWhite::WIN;
}

bool Chess::Game::isSquareAttacked(const ChessboardPosition& square, const PieceColor& colorUnderAttack, const Board& board) const
{
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

bool Chess::Game::isEnPassantPosition(const UniversalVector<int8_t>& position) const
{
    return enPassantPosition && enPassantPosition->getX() == position.x && enPassantPosition->getY() == position.y;
}

void Chess::Game::addPossibleMovesEnPassant(const Piece *piece, std::vector<ChessMove>& possibleMoves) const
{
    if(!piece->type == PieceType::PAWN)
        return;

    const int8_t dir = piece->color == PieceColor::CHESS_WHITE ? -1 : 1;

    //en passant left check
    UniversalVector<int8_t> left = {(int8_t)(piece->getPosition().getX() + 1), piece->getPosition().getY()};
    if(isEnPassantPosition(left))
        possibleMoves.emplace_back(piece->getPosition(), ChessboardPosition(left.x, left.y + dir), ChessMoveType::CAPTURE | ChessMoveType::EN_PASSANT, PieceType::PAWN);

    //en passant right check
    UniversalVector<int8_t> right = {(int8_t)(piece->getPosition().getX() - 1), piece->getPosition().getY()};
    if(isEnPassantPosition(right))
        possibleMoves.emplace_back(piece->getPosition(), ChessboardPosition(right.x, right.y + dir), ChessMoveType::CAPTURE | ChessMoveType::EN_PASSANT, PieceType::PAWN);

}

void Chess::Game::addPossibleMovesCastle(const Piece *piece, std::vector<ChessMove> &possibleMoves) const
{
    if(piece->type != PieceType::KING || piece->hasMoved() || isCheck(piece->color, board))
        return;
    addPossibleMovesCastleShort(piece, possibleMoves);
    addPossibleMovesCastleLong(piece, possibleMoves);
}

void Chess::Game::addPossibleMovesCastleShort(const Piece *king, std::vector<ChessMove> &possibleMoves) const
{
    const int8_t y = king->getPosition().getY();
    
    for(int8_t x = king->getPosition().getX() + 1; x < board.WIDTH - 1; ++x)
    {
        if(board.getPiece(x, y) || isSquareAttacked({x, y}, king->color, board))
            return;
    }

    const Piece* const rook = board.getPiece(board.WIDTH - 1, y);

    if(!rook || rook->type != PieceType::ROOK || rook->hasMoved())
        return;

    possibleMoves.emplace_back(king->getPosition(), ChessboardPosition(king->getPosition().getX() + 2, y), ChessMoveType::SHORT_CASTLE);
}

void Chess::Game::addPossibleMovesCastleLong(const Piece *king, std::vector<ChessMove> &possibleMoves) const
{
    const int8_t y = king->getPosition().getY();
    
    for(int8_t x = king->getPosition().getX() - 1; x > 0; --x)
    {
        if(board.getPiece(x, y) || isSquareAttacked({x, y}, king->color, board))
            return;
    }

    const Piece* const rook = board.getPiece(0, y);

    if(!rook || rook->type != PieceType::ROOK || rook->hasMoved())
        return;

    possibleMoves.emplace_back(king->getPosition(), ChessboardPosition(king->getPosition().getX() - 2, y), ChessMoveType::LONG_CASTLE);
}
