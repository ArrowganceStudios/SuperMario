/**
 * @file        Game.cpp
 * @author      mg6 (maciej@gamrat.it)
 * @date        2014-2015
 * @copyright   GNU GPL v2
 */

#include "Game.hpp"

using namespace Mario;

Game::Game()
{
    done = false;
    player = nullptr;
    map = new Map(this, ASSETS "map1");

    log_info("[Game]\tCreated.");
}

Game::~Game()
{
    player = nullptr;
    delete map;

    log_info("[Game]\tDeleted.");
}

void Game::LoadMap(std::string path)
{
    map->Load(path);
}

void Game::SaveMap(std::string path)
{
    map->Save(path);
}

void Game::Update(float dt)
{
    if (!states.empty() && states.back()->OnUpdate(dt))
        return;

    map->Update(dt);
    if (player) map->offset = (player->pos_x > 5*TileSize) ? player->pos_x - 5*TileSize : 0;
}

bool Game::IsPaused()
{
    for (std::list<GameState*>::iterator i = states.begin(); i != states.end(); ++i)
        if (GamePausedState* paused = dynamic_cast<GamePausedState*>(*i))
            return true;

    return false;
}

void Game::OnGameStateFinish(GameState* state)
{
    states.remove(state);
    // delete state; // unnecessary, Valgrind indicates twice freeing error
}

void Game::OnKill(Object* killer, Object* victim)
{
    if (Player* player = dynamic_cast<Player*>(victim))
    {
        log_info("[Game]\tPlayer killed.");
        states.push_back(new GameOverState(this));
    }
}

void Game::OnPlayerAddToMap(Player* player)
{
    this->player = player;

    log_info("[Map]\tPlayer added.");
}

void Game::OnObjectAddToMap(Object* object)
{
    log_info("[Map]\tObject added.");
}

void Game::OnObjectOutOfMap(Object* object)
{
    log_info("[Map]\tObject out of map.");

    if (Player* player = dynamic_cast<Player*>(object))
    {
        this->player = nullptr;
        states.push_back(new GameOverState(this));
    }
}
