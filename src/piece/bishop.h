#pragma once

#include "piece.h"

class Bishop : public Piece
{
public:
    Bishop(int x, int y, Color color);
    Bitmask getLegalMoves(Bitmask alliedPositions, Bitmask enemyPositions);
    Bitmask getAttackedSquares(Bitmask alliedPositions, Bitmask enemyPositions);
};
