#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "piece/piece.h"
#include "piece/king.h"
#include "bitmask.h"

class Board
{
private:
    std::vector<std::unique_ptr<Piece>> pieces;
    int xSize, ySize;
    float xOffset, yOffset, squareSize;
    King* king[2];

    sf::FloatRect bBox;
    sf::RectangleShape square;

    void MakeInitial();

public:
    Board();
    void Draw(sf::RenderWindow& window, Bitmask mask);
    void ResetPosition(Piece& piece);
    void Move(Piece& piece, int x, int y);
    void Remove(Piece* piece);

    bool hasPiece(int x, int y);
    Piece* getPiece(int x, int y);
    Piece::PieceSet getPieces();
    Bitmask getPositions(Piece::Color color);
    Bitmask getAttackedPositions(Piece::Color color);
    Piece* getKing(Piece::Color color);
    bool canRefuteCheck(Piece::Color color);

    bool posIsOver(sf::Vector2i positon);
    std::pair<int, int> posToCoords(sf::Vector2f pos);
};
