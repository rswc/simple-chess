#include "king.h"

King::King(int x, int y, Color color) : Piece(x, y, color)
{
    sprite.setTextureRect(sf::IntRect(60, 60 * color, 60, 60));
}

Bitmask King::getLegalMoves(Bitmask allied, Bitmask enemy)
{
    Bitmask bm = Bitmask(Bitmask::EMPTY);

    for (int i = x - 1; i <= x + 1; i++)
        for (int j = y - 1; j <= y + 1; j++)
            bm.set(i, j);

    bm.set(x, y, false);

    return bm & ~allied;
}

Bitmask King::getAttackedSquares(Bitmask alliedPositions, Bitmask enemyPositions)
{
    return getLegalMoves(alliedPositions, enemyPositions);
}
