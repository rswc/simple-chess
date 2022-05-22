#pragma once

#include "piece.h"

class Pawn : public Piece
{
public:
    Pawn(int x, int y, Color color);
    Bitmask getLegalMoves(Bitmask alliedPositions, Bitmask enemyPositions);
    Bitmask getAttackedSquares(Bitmask alliedPositions, Bitmask enemyPositions);
};
