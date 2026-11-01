#pragma once
#include"../Core/Game.hpp"
#include"raylib.h"
namespace Chess
{
    class InputHandler
    {
        public:
            void proccessInput(Game& game) const;
        private:
            void proccessMouseInput(Game& game) const;
    };
};