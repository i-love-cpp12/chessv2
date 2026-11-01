#include "InputHandler.hpp"
#include"../../config/config.hpp"

void Chess::InputHandler::proccessInput(Game &game) const
{
    proccessMouseInput(game);
}

void Chess::InputHandler::proccessMouseInput(Game &game) const
{
    const uint8_t CELL_WIDTH = Config::boardWidthOnScreen / Board::WIDTH;
    const uint8_t CELL_HEIGHT = Config::boardHeightOnScreen / Board::HEIGHT;

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Vector2 mousePosition = GetMousePosition();

        game.onSquereSelected(
            (mousePosition.x - Config::boardOnScreenX) / CELL_WIDTH,
            (mousePosition.y - Config::boardOnScreenY) / CELL_HEIGHT
        );
    }

    //example
    const int mouseWheelChange = GetMouseWheelMove() * 20;

    Config::boardHeightOnScreen += mouseWheelChange;
    Config::boardWidthOnScreen += mouseWheelChange;

    if(Config::boardWidthOnScreen < 10 || Config::boardHeightOnScreen < 10)
    {
        Config::boardWidthOnScreen = 10;
        Config::boardHeightOnScreen = 10;
        return;
    }

    Config::boardOnScreenX -= mouseWheelChange / 2;
    Config::boardOnScreenY -= mouseWheelChange / 2;
}
