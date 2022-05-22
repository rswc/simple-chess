#pragma once

#include <map>
#include <SFML/Graphics.hpp>

class Resources
{
private:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;
    Resources() = default;
public:
    static const float PieceSpriteSize;

    void LoadTextures();
    sf::Texture& GetTexture(std::string name);
    void LoadFonts();
    sf::Font& GetFont(std::string name);
    static Resources& GetInstance();
};
