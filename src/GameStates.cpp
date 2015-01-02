#include "GameStates.hpp"
#include "Game.hpp"

using namespace Mario;

void GameState::OnFinish()
{
    game->OnGameStateFinish(this);
}

bool GamePausedState::OnKeyDown(int key)
{
    if (key == ALLEGRO_KEY_P)
        Finish();

    return true;
}

bool GamePausedState::OnUpdate(float dt)
{
    return true;
}

bool GameOverState::OnUpdate(float dt)
{
    timer += dt;

    if (timer > 5)
    {
        Finish();
        game->done = true;
    }

    return true;
}
