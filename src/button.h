#pragma once

#include <SFML/Graphics.hpp>

class Button
{
private:
    float x, y, xm, ym;
    sf::Text text;
    sf::RectangleShape background;

public:
    void Draw(sf::RenderWindow& window);
    
    bool posIsOver(sf::Vector2i positon);

    Button(float xOffset, float yOffset, float xMargin, float yMargin, const std::string& label);
};

