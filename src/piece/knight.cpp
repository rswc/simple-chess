#include "knight.h"

#include <math.h>

Knight::Knight(int x, int y, Color color) : Piece(x, y, color)
{
    sprite.setTextureRect(sf::IntRect(180, 60 * color, 60, 60));
}

Bitmask Knight::getLegalMoves(Bitmask allied, Bitmask enemy)
{
    Bitmask bm = Bitmask(Bitmask::EMPTY);

    for (int i = x - 2; i <= x + 2; i++)
        for (int j = y - 2; j <= y + 2; j++)
            bm.set(i, j, abs(x - i) + abs(y - j) == 3);

    return bm & ~allied;
}

Bitmask Knight::getAttackedSquares(Bitmask alliedPositions, Bitmask enemyPositions)
{
    return getLegalMoves(alliedPositions, enemyPositions);
}
