#include "resources.h"

#include <iostream>

const float Resources::PieceSpriteSize = 60.0;

void Resources::LoadTextures()
{
    textures["pieces"] = sf::Texture();
    textures["pieces"].loadFromFile("./res/pieces.png");
}

sf::Texture& Resources::GetTexture(std::string name)
{
    return textures[name];
}

void Resources::LoadFonts()
{
    fonts["opensans"] = sf::Font();
    fonts["opensans"].loadFromFile("./res/Open_Sans/OpenSans-Light.ttf");
}

sf::Font& Resources::GetFont(std::string name)
{
    return fonts[name];
}

Resources& Resources::GetInstance()
{
    static Resources instance;
    return instance;
}
