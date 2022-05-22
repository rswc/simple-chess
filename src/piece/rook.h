#pragma once

#include "piece.h"

class Rook : public Piece
{
public:
    Rook(int x, int y, Color color);
    Bitmask getLegalMoves(Bitmask alliedPositions, Bitmask enemyPositions);
    Bitmask getAttackedSquares(Bitmask alliedPositions, Bitmask enemyPositions);
};
