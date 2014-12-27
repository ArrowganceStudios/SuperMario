#include "common.hpp"
#include "gamemanager.hpp"

int main(int argc, char** argv)
{
    Mario::GameManager game;

    game.init();
    game.loop();
    game.cleanup();

    return 0;
}
