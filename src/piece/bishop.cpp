#include "bishop.h"

#define PC_BM_CAST_STEP(x, y) bm.set(x, y); if (both.get(x, y)) break;

Bishop::Bishop(int x, int y, Color color) : Piece(x, y, color)
{
    sprite.setTextureRect(sf::IntRect(240, 60 * color, 60, 60));
}

Bitmask Bishop::getLegalMoves(Bitmask allied, Bitmask enemy)
{
    Bitmask bm = Bitmask(Bitmask::EMPTY);

    auto both = allied | enemy;

    for (int i = x + 1, j = y + 1; i < 8 && j < 8; i++, j++)
    {
        PC_BM_CAST_STEP(i, j);
    }
    for (int i = x + 1, j = y - 1; i < 8 && j >= 0; i++, j--)
    {
        PC_BM_CAST_STEP(i, j);
    }
    for (int i = x - 1, j = y + 1; i >= 0 && j < 8; i--, j++)
    {
        PC_BM_CAST_STEP(i, j);
    }
    for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--)
    {
        PC_BM_CAST_STEP(i, j);
    }

    return bm & ~allied;
}

Bitmask Bishop::getAttackedSquares(Bitmask alliedPositions, Bitmask enemyPositions)
{
    return getLegalMoves(alliedPositions, enemyPositions);
}
