#include "piece.h"

#include "resources.h"

bool Piece::PieceSet::hasPiece(int x, int y)
{
    for (auto& piece : pieces)
        if (piece->getX() == x && piece->getY() == y)
            return true;
    
    return false;
}

Piece* Piece::PieceSet::getPiece(int x, int y)
{
    for (auto& piece : pieces)
        if (piece->getX() == x && piece->getY() == y)
            return piece;
    
    return nullptr;
}

void Piece::PieceSet::addPiece(Piece* pc)
{
    pieces.push_back(pc);
}

Piece::Piece(int x, int y, Color color) : x(x), y(y), color(color)
{
    sprite.setPosition(100, 100);
    sprite.setTexture(Resources::GetInstance().GetTexture("pieces"));
}

void Piece::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

int Piece::getX()
{
    return x;
}

int Piece::getY()
{
    return y;
}

Piece::Color Piece::getColor()
{
    return color;
}

void Piece::setX(int x)
{
    this->x = x;
}

void Piece::setY(int y)
{
    this->y = y;
}

void Piece::setMoved(bool v)
{
    hasMoved = v;
}

void Piece::setSpritePos(float x, float y)
{
    sprite.setPosition(x, y);
}

void Piece::setScale(float x, float y)
{
    sprite.setScale(x / Resources::PieceSpriteSize, y / Resources::PieceSpriteSize);
}
