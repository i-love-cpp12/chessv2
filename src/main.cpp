#include"raylib.h"
#include<iostream>
#include"Core/Game.hpp"
#include"Rendering/Renderer.hpp"

int main()
{
    // Chess::Board();
    // std::cout<<Chess::ChessboardPosition("e4").getChessNotationPosition()<<" "<<(int)Chess::ChessboardPosition(1, 9).getX()<<" "<<(int)Chess::ChessboardPosition(1, 9).getY();
    // std::cin.get();
    Chess::Game game;
    Chess::Renderer renderer("../textures/chess_texture_sheet_1.png", "../config/textureCoords.json");

    while(!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(WHITE);
            renderer.renderGame(game);
        EndDrawing();
    }
    return 0;
}