#include "board.h"

#include "piece/all.h"

#define MAKE_PIECE(type, x, y, color) pieces.push_back(std::move(std::make_unique<type>(x, y, color)));
#define MIRROR_PIECE(type, x) MAKE_PIECE(type, x, 0, Piece::BLACK); MAKE_PIECE(type, x, 7, Piece::WHITE);
#define MAKE_FOUR(type, x) MIRROR_PIECE(type, x); MIRROR_PIECE(type, 7 - x);

void Board::MakeInitial()
{
    for (int i = 0; i < 8; i++)
    {
        MAKE_PIECE(Pawn, i, 1, Piece::BLACK);
        MAKE_PIECE(Pawn, i, 6, Piece::WHITE);
    }

    MAKE_FOUR(Rook, 0);
    MAKE_FOUR(Knight, 1);
    MAKE_FOUR(Bishop, 2);

    MIRROR_PIECE(Queen, 4);

    auto pc = std::make_unique<King>(3, 0, Piece::BLACK);
    king[Piece::BLACK] = pc.get();
    pieces.push_back(std::move(pc));

    pc = std::make_unique<King>(3, 7, Piece::WHITE);
    king[Piece::WHITE] = pc.get();
    pieces.push_back(std::move(pc));

    for (auto& piece : pieces)
    {
        ResetPosition(*piece);
        piece->setScale(squareSize, squareSize);
    }
}

Board::Board() : xSize(8), ySize(8), xOffset(60.0), yOffset(60.0), squareSize(60.0)
{
    square = sf::RectangleShape(sf::Vector2f(squareSize, squareSize));
    bBox = sf::FloatRect(xOffset, yOffset, xSize * squareSize, ySize * squareSize);
    
    MakeInitial();
}

void Board::Draw(sf::RenderWindow& window, Bitmask mask)
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            sf::Color c = ((i+j) % 2) ? sf::Color(180, 180, 180) : sf::Color(140, 140, 140);

            if (mask.get(i, j))
                c *= sf::Color(150, 150, 220);

            square.setFillColor(c);
            square.setPosition(xOffset + i * squareSize, yOffset + j * squareSize);
            window.draw(square);    
        }
    
    for (auto& piece : pieces)
        piece->Draw(window);
}

void Board::ResetPosition(Piece& piece)
{
    piece.setSpritePos(xOffset + piece.getX() * squareSize, yOffset + piece.getY() * squareSize);
}

void Board::Move(Piece& piece, int x, int y)
{
    piece.setX(x);
    piece.setY(y);
    piece.setMoved(true);
    ResetPosition(piece);
}

void Board::Remove(Piece* piece)
{
    for (int i = 0; i < pieces.size(); i++)
        if (pieces[i].get() == piece)
        {
            pieces.erase(pieces.begin() + i);
            return;
        }
}

bool Board::hasPiece(int x, int y)
{
    for (auto& piece : pieces)
        if (piece->getX() == x && piece->getY() == y)
            return true;
    
    return false;
}

Piece* Board::getPiece(int x, int y)
{
    for (auto& piece : pieces)
        if (piece->getX() == x && piece->getY() == y)
            return piece.get();
    
    return nullptr;
}

Piece::PieceSet Board::getPieces()
{
    auto ps = Piece::PieceSet();
    for (auto& piece : pieces)
        ps.addPiece(piece.get());
    
    return ps;
}

Bitmask Board::getPositions(Piece::Color color)
{
    Bitmask bm = Bitmask(Bitmask::EMPTY);

    for (auto& piece : pieces)
        bm.set(piece->getX(), piece->getY(), piece->getColor() == color);

    return bm;
}

Bitmask Board::getAttackedPositions(Piece::Color color)
{
    Bitmask bm = Bitmask(Bitmask::EMPTY);

    auto allied = getPositions(static_cast<Piece::Color>(!color));
    auto enemy = getPositions(color);

    for (auto& piece : pieces)
    {
        if (piece->getColor() == color)
            continue;
        bm |= piece->getAttackedSquares(allied, enemy);
    }

    return bm;
}

Piece* Board::getKing(Piece::Color color)
{
    return king[color];
}

bool Board::posIsOver(sf::Vector2i position)
{
    return bBox.contains((sf::Vector2f)position);
}

std::pair<int, int> Board::posToCoords(sf::Vector2f pos)
{
    return std::pair<int, int>((pos.x - xOffset) / squareSize, (pos.y - yOffset) / squareSize);
}
