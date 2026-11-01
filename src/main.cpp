#include"raylib.h"
#include<iostream>
#include"Core/Game.hpp"
#include"Rendering/Renderer.hpp"
#include"Input/InputHandler.hpp"

int main()
{
    Chess::Game game;
    Chess::Renderer renderer("../textures/chess_texture_sheet_1.png", "../config/textureCoords.json");
    Chess::InputHandler inputHandler;
    while(!WindowShouldClose())
    {
        inputHandler.proccessInput(game);
            
        BeginDrawing();
            ClearBackground(WHITE);
            renderer.renderGame(game);
        EndDrawing();
    }
    return 0;
}