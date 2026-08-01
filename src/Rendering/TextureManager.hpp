#pragma once

#include"../../libs/json.hpp"
#include<raylib.h>
#include<map>

namespace Chess
{
    class TextureManager
    {
        public:
            TextureManager() = default;
            TextureManager(const std::string& texturePath, const std::string& JSONCoordsPath);

            const Texture2D& getTexture() const;
            const Rectangle& getSprite(const std::string& spriteName) const;
        private:
            static std::map<std::string, Rectangle> spriteMap;
            static Texture2D texture; 
            static uint32_t CELL_SIZE;  
            static bool alreadyLoaded;
    };
}