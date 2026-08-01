#include "TextureManager.hpp"
#include<fstream>
#include<stdexcept>

std::map<std::string, Rectangle> Chess::TextureManager::spriteMap = {}; 
Texture2D Chess::TextureManager::texture;
uint32_t Chess::TextureManager::CELL_SIZE;
bool Chess::TextureManager::alreadyLoaded = false; 

Chess::TextureManager::TextureManager(const std::string& texturePath, const std::string& JSONCoordsPath)
{
    if(alreadyLoaded)
        return;

    texture = LoadTexture(texturePath.c_str());

    if(texture.id <= 0)
        throw std::runtime_error("Texture failed to load");

    CELL_SIZE = texture.width / 8;

    std::ifstream coordsFile(JSONCoordsPath);

    if(!coordsFile)
        throw std::runtime_error("Failed to load JSONCoordsFile");

    nlohmann::json JSON;
    JSON << coordsFile;

    for(const auto& sprite : JSON)
    {
        if(!sprite.contains("name") || !sprite.contains("rect"))
            throw std::runtime_error(
                "Invalid texture atlas format"
            );

        const auto& rect = sprite["rect"];

        if(!rect.contains("x") || !rect.contains("y") || !rect.contains("width") || !rect.contains("height"))
            throw std::runtime_error(
                "Invalid texture atlas format"
            );

        spriteMap[sprite["name"]] = Rectangle{
            rect.at("x").get<float>() * CELL_SIZE,
            rect.at("y").get<float>() * CELL_SIZE,
            rect.at("width").get<float>() * CELL_SIZE,
            rect.at("height").get<float>() * CELL_SIZE
        };
    }
    alreadyLoaded = true;
}

const Texture2D &Chess::TextureManager::getTexture() const
{
    return texture;
}

const Rectangle &Chess::TextureManager::getSprite(const std::string &spriteName) const
{
    return spriteMap.at(spriteName);
}
