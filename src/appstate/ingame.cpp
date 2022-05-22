#include "ingame.h"

#include "resources.h"

#include <sstream>

void Ingame::Draw(sf::RenderWindow& window)
{
    board.Draw(window, legalMoves);

    if (grabbedPiece != nullptr)
    {
        sf::Vector2i pos = sf::Mouse::getPosition(window);
        grabbedPiece->setSpritePos(pos.x, pos.y);
    }
    
    window.draw(infoText);
    btnConcede.Draw(window);
}

void Ingame::Input(sf::RenderWindow& window, sf::Event& event)
{   
    if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2i pos = sf::Mouse::getPosition(window);

        // Process click on button
        if (btnConcede.posIsOver(pos))
        {
            if (winstate)
            {
                // exit to menu
                requestExit = true;
            }
            else
            {
                triggerWinstate();
                updateInfoText();
            }
        }

        // Process click on board
        if (board.posIsOver(pos) && !winstate)
        {
            auto coords = board.posToCoords((sf::Vector2f)pos);

            if (grabbedPiece == nullptr)
            {
                if (board.hasPiece(coords.first, coords.second))
                {
                    // grab piece
                    grabbedPiece = board.getPiece(coords.first, coords.second);

                    if (grabbedPiece->getColor() != activePlayer)
                    {
                        grabbedPiece = nullptr;
                        return;
                    }

                    auto allied = board.getPositions(activePlayer);
                    auto enemy = board.getPositions(static_cast<Piece::Color>(!activePlayer));
                    legalMoves = grabbedPiece->getLegalMoves(allied, enemy);
                
                    if (grabbedPiece == board.getKing(activePlayer))
                        legalMoves &= ~underAttack;
                }
            }
            else if (legalMoves.get(coords.first, coords.second))
            {
                if (board.hasPiece(coords.first, coords.second))
                {
                    // do attack
                    board.ResetPosition(*grabbedPiece);

                    auto other = board.getPiece(coords.first, coords.second);

                    if (other == board.getKing(static_cast<Piece::Color>(!activePlayer)))
                    {
                        triggerWinstate();
                    }

                    board.Remove(other);

                }

                // do move
                board.Move(*grabbedPiece, coords.first, coords.second);

                activePlayer = static_cast<Piece::Color>(!activePlayer);
                underAttack = board.getAttackedPositions(activePlayer);

                grabbedPiece = nullptr;
                legalMoves = Bitmask(Bitmask::EMPTY);

                ++turn;

                updateInfoText();

            }
            else
            {
                board.ResetPosition(*grabbedPiece);

                grabbedPiece = nullptr;
                legalMoves = Bitmask(Bitmask::EMPTY);
            }
        }
    }
}

Appstate::StateChange Ingame::DoStateChange()
{
    return (requestExit) ? MENU : NONE;
}

Ingame::Ingame()
{
    grabbedPiece = nullptr;
    underAttack = board.getAttackedPositions(activePlayer);
    
    updateInfoText();
    infoText.setFont(Resources::GetInstance().GetFont("opensans"));
    infoText.setPosition(70.0, 600.0);
    infoText.setCharacterSize(28);
    infoText.setFillColor(sf::Color::Black);
}

void Ingame::updateInfoText()
{
    std::ostringstream s;

    if (winstate)
    {
        s << ((activePlayer != Piece::WHITE) ? "White" : "Black") << " wins.";
    }
    else
    {
        s << "Turn " << turn << ": ";
        s << ((activePlayer == Piece::WHITE) ? "White" : "Black") << " to move.";

        auto king = board.getKing(activePlayer);
        if (underAttack.get(king->getX(), king->getY()))
            s << "\n" << ((activePlayer == Piece::WHITE) ? "White" : "Black") << " king in check!\n";

    }

    infoText.setString(s.str());
}

void Ingame::triggerWinstate()
{
    winstate = true;
    btnConcede = Button(80.0, 680.0, 40.0, 5.0, "Exit");
}
