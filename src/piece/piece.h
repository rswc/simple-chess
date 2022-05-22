#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "bitmask.h"

class Piece
{
public:
    enum Color
    {
        BLACK,
        WHITE
    };

    struct PieceSet
    {
    private:
        std::vector<Piece*> pieces;
    public:
        bool hasPiece(int x, int y);
        Piece* getPiece(int x, int y);
        void addPiece(Piece* pc);
    };

protected:
    int x, y;
    sf::Sprite sprite;
    Color color;
    bool hasMoved = false;
public:
    Piece(int x, int y, Color color);
    void Draw(sf::RenderWindow& window);
    
    virtual Bitmask getLegalMoves(Bitmask alliedPositions, Bitmask enemyPositions) = 0;
    virtual Bitmask getAttackedSquares(Bitmask alliedPositions, Bitmask enemyPositions) = 0;

    int getX();
    int getY();
    Color getColor();
    void setX(int x);
    void setY(int y);
    void setMoved(bool v);
    void setSpritePos(float x, float y);
    void setScale(float x, float y);
};

