#include "pawn.h"

Pawn::Pawn(int x, int y, Color color) : Piece(x, y, color)
{
    sprite.setTextureRect(sf::IntRect(300, 60 * color, 60, 60));
}

Bitmask Pawn::getLegalMoves(Bitmask allied, Bitmask enemy)
{
    Bitmask bm = Bitmask(Bitmask::EMPTY);

    int fwd = color ? -1 : 1;

    auto both = allied | enemy;

    if (!both.get(x, y + fwd))
    {
        bm.set(x, y + fwd);
        bm.set(x, y + 2 * fwd, !(hasMoved || both.get(x, y + 2 * fwd)));
    }

    bm.set(x + 1, y + fwd, enemy.get(x + 1, y + fwd));
    bm.set(x - 1, y + fwd, enemy.get(x - 1, y + fwd));

    return bm & (~allied);
}

Bitmask Pawn::getAttackedSquares(Bitmask alliedPositions, Bitmask enemyPositions)
{
    Bitmask bm = Bitmask(Bitmask::EMPTY);

    int fwd = color ? -1 : 1;

    bm.set(x + 1, y + fwd);
    bm.set(x - 1, y + fwd);

    return bm;
}
