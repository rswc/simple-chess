#pragma once

#include "piece.h"

class Queen : public Piece
{
public:
    Queen(int x, int y, Color color);
    Bitmask getLegalMoves(Bitmask alliedPositions, Bitmask enemyPositions);
    Bitmask getAttackedSquares(Bitmask alliedPositions, Bitmask enemyPositions);
};
