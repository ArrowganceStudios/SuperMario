/**
 * @file        GameStates.cpp
 * @author      mg6 (maciej@gamrat.it)
 * @date        2014-2015
 * @copyright   GNU GPL v2
 */

#include "GameStates.hpp"
#include "Game.hpp"
#include "GameManager.hpp"

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
        if (game->num_lives == 0)
            game->done = true;
        else
            game->Start();

        Finish();

        return true;
    }
    else
        timer -= dt;

    if (game->player)
        game->player->OnUpdate(dt);

    return true;
}

bool KeyInfoState::OnKeyDown(int key)
{
    if (key == ALLEGRO_KEY_H)
        Finish();

    return true;
}

/**
 * Shorthand for string displaying.
 * @param where Y coordinate.
 * @param what String to display.
 */
#define puts(where, what)   game_mgr->PutString(game_mgr->width/2, where, 0xFFFFFF, ALLEGRO_ALIGN_CENTER, what)

bool KeyInfoState::OnDraw(GameManager* game_mgr)
{
    puts(50,  "X - Run");
    puts(70,  "Z - Jump");
    puts(90,  "P - Pause");

    puts(130, "Esc - Quit the game");
    puts(150, "F1 - Toggle map edit");
    puts(170, "F2 - Save map to file");
    puts(190, "F3 - Load map from file");

    puts(230, "H - Help/dismiss");

    return false;
}

#undef puts

bool LevelClearState::OnDraw(GameManager* game_mgr)
{
    game_mgr->PutString(game_mgr->width/2, game_mgr->height/2+20, 0xFFFFFF, ALLEGRO_ALIGN_CENTER, "Level clear");
    game_mgr->PutString(game_mgr->width/2, game_mgr->height/2, 0xFFFFFF, ALLEGRO_ALIGN_CENTER, "Congratulations!");

    return true;
}

bool LevelClearState::OnUpdate(float dt)
{
    if (timer <= dt)
    {
        game->done = true;
        Finish();

        return true;
    }
    else
        timer -= dt;

    return true;
}
