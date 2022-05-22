#pragma once

#include "piece.h"

class Knight : public Piece
{
public:
    Knight(int x, int y, Color color);
    Bitmask getLegalMoves(Bitmask alliedPositions, Bitmask enemyPositions);
    Bitmask getAttackedSquares(Bitmask alliedPositions, Bitmask enemyPositions);
};
