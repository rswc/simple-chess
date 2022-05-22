#include <SFML/Graphics.hpp>

#include "resources.h"
#include "appstate/appstate.h"
#include "appstate/ingame.h"
#include "appstate/menu.h"
#include "bitmask.h"

Appstate* state;

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 800), "big window");
    window.setFramerateLimit(30);

    Resources& res = Resources::GetInstance();
    res.LoadTextures();
    res.LoadFonts();

    state = new Menu();
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        
        case sf::Event::MouseButtonPressed:
            state->Input(window, event);
            break;
        }

        switch (state->DoStateChange())
        {
        case Appstate::INGAME:
            delete state;
            state = new Ingame();
            break;

        case Appstate::MENU:
            delete state;
            state = new Menu();
            break;
        
        case Appstate::QUIT:
            delete state;
            return 0;
        }

        window.clear(sf::Color(230, 230, 230));
        state->Draw(window);
        
        window.display();
    }
    
    delete state;
}
