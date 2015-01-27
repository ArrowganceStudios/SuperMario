#include "Common.hpp"
#include "GameManager.hpp"

using namespace Mario;

int main(int argc, char** argv)
{
    GameManager game;

    try
    {
        log_info("[Mario]\tLoading...");

        game.Init();
        game.Loop();
        game.Cleanup();

        log_info("[Mario]\tGame finished successfuly.");
    }
    catch (std::runtime_error& e)
    {
        log_error("[!!]", e.what());
    }

    return 0;
}
