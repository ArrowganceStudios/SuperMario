/**
 * @file        GameStates.cpp
 * @author      mg6 (maciej@gamrat.it)
 * @date        2014-2015
 * @copyright   GNU GPL v2
 */

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

void GameOverState::OnInit()
{
    if (Player* player = game->player)
    {
        player->dir_x = 0;
        player->dir_y = 15 * TileSize;
        player->state |= STATE_FALL;
    }

    if (game->num_lives > 0)
        --game->num_lives;
}

bool GameOverState::OnUpdate(float dt)
{
    if (timer <= dt)
    {
        Finish();

        if (game->num_lives == 0)
            game->done = true;
        else
            game->Start();

        return true;
    }
    else
        timer -= dt;

    if (game->player)
        game->player->OnUpdate(dt);

    return true;
}
