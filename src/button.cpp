#include "button.h"

#include "resources.h"

void Button::Draw(sf::RenderWindow& window)
{
    window.draw(background);
    window.draw(text);
}

bool Button::posIsOver(sf::Vector2i positon)
{
    return background.getGlobalBounds().contains((sf::Vector2f)positon);
}

Button::Button(float xOffset, float yOffset, float xMargin, float yMargin, const std::string& label) : x(xOffset), y(yOffset), xm(xMargin), ym(yMargin)
{
    text.setFont(Resources::GetInstance().GetFont("opensans"));
    text.setPosition(x + xm, y + ym);
    text.setCharacterSize(28);
    text.setFillColor(sf::Color::Black);
    text.setString(label);

    auto tb = text.getLocalBounds();

    background.setPosition(x, y);
    background.setSize(sf::Vector2f(tb.width + 2 * xm, tb.height + 15.0 + 2 * ym));
    background.setFillColor(sf::Color(180, 190, 240));
}
