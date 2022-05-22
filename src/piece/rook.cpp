#include "rook.h"

#define PC_BM_CAST_STEP(x, y) bm.set(x, y); if (both.get(x, y)) break;

Rook::Rook(int x, int y, Color color) : Piece(x, y, color)
{
    sprite.setTextureRect(sf::IntRect(120, 60 * color, 60, 60));
}

Bitmask Rook::getLegalMoves(Bitmask allied, Bitmask enemy)
{
    Bitmask bm = Bitmask(Bitmask::EMPTY);

    auto both = allied | enemy;

    for (int i = x + 1; i < 8; i++)
    {
        PC_BM_CAST_STEP(i, y);
    }
    for (int i = x - 1; i >= 0; i--)
    {
        PC_BM_CAST_STEP(i, y);
    }
    for (int i = y + 1; i < 8; i++)
    {
        PC_BM_CAST_STEP(x, i);
    }
    for (int i = y - 1; i >= 0; i--)
    {
        PC_BM_CAST_STEP(x, i);
    }

    return bm & ~allied;
}

Bitmask Rook::getAttackedSquares(Bitmask alliedPositions, Bitmask enemyPositions)
{
    return getLegalMoves(alliedPositions, enemyPositions);
}
