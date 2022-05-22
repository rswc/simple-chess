#pragma once
#include <SFML/Graphics.hpp>

class Appstate
{
public:
    enum StateChange
    {
        NONE,
        QUIT,
        MENU,
        INGAME
    };

    virtual void Draw(sf::RenderWindow& window) = 0;
    virtual void Input(sf::RenderWindow& window, sf::Event& event) = 0;
    virtual StateChange DoStateChange() = 0;
};
