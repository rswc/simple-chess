#pragma once

#include <SFML/Graphics.hpp>

#include "appstate/appstate.h"
#include "button.h"

class Menu : public Appstate
{
private:
    sf::Text title;
    Button btnStart = Button(80.0, 400.0, 40.0, 8.0, "Start");
    Button btnQuit = Button(80.0, 500.0, 40.0, 5.0, "Quit");
    StateChange requestedState = NONE;

public:
    void Draw(sf::RenderWindow& window);
    void Input(sf::RenderWindow& window, sf::Event& event);
    StateChange DoStateChange();
    Menu();
};
