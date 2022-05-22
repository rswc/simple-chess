#pragma once

#include "appstate.h"
#include "board.h"
#include "button.h"

class Ingame : public Appstate
{
private:
    Board board;
    Piece* grabbedPiece;
    Bitmask legalMoves = Bitmask(Bitmask::EMPTY);
    Bitmask underAttack;
    Piece::Color activePlayer = Piece::WHITE;
    int turn = 1;
    bool winstate = false, requestExit = false;

    sf::Text infoText;
    Button btnConcede = Button(80.0, 680.0, 40.0, 5.0, "Concede");

    void updateInfoText();
    void triggerWinstate();

public:
    void Draw(sf::RenderWindow& window);
    void Input(sf::RenderWindow& window, sf::Event& event);
    StateChange DoStateChange();
    Ingame();
};
