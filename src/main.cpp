#include"raylib.h"
#include<iostream>
#include"Core/Game.hpp"
#include"Rendering/Renderer.hpp"

int main()
{
    Chess::Game game;
    Chess::Renderer renderer("../textures/chess_texture_sheet_1.png", "../config/textureCoords.json");

    while(!WindowShouldClose())
    {
        //temp
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            game.onSquereSelected(GetMouseX() / 100, GetMouseY() / 100);
            
        BeginDrawing();
            ClearBackground(WHITE);
            renderer.renderGame(game);
        EndDrawing();
    }
    return 0;
}