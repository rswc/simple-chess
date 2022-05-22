#include "menu.h"

#include "resources.h"

void Menu::Draw(sf::RenderWindow& window)
{
    window.draw(title);
    btnStart.Draw(window);
    btnQuit.Draw(window);
}

void Menu::Input(sf::RenderWindow& window, sf::Event& event)
{   
    if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2i pos = sf::Mouse::getPosition(window);

        if (btnStart.posIsOver(pos))
            requestedState = INGAME;

        else if (btnQuit.posIsOver(pos))
            requestedState = QUIT;
    }
}

Appstate::StateChange Menu::DoStateChange()
{
    return requestedState;
}

Menu::Menu()
{
    title.setFont(Resources::GetInstance().GetFont("opensans"));
    title.setPosition(70.0, 100.0);
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::Black);
    title.setString("it's chess time");
}
