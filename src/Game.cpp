/**
 * @file        Game.cpp
 * @author      mg6 (maciej@gamrat.it)
 * @date        2014-2015
 * @copyright   GNU GPL v2
 */

#include "Game.hpp"

using namespace Mario;

Game::Game() : done(false), map(nullptr), player(nullptr), num_lives(3), points(0)
{
    log_info("[Game]\tCreated.");

    Start();

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

void Game::Start()
{
    log_info("[Game]\tStarted with", num_lives, "lives.");

    if (map)
        delete map;

    map = new Map(this, ASSETS "map1");
}

void Game::Update(float dt)
{
    if (!states.empty() && states.back()->OnUpdate(dt))
        return;

    map->Update(dt);

    if (player)
    {
        if ((map->offset = player->pos_x - 10.0f * TileSize) < 0)
            map->offset = 0;

        if (player->pos_x >= (map->tiles.size() - 1) * float(TileSize))
            states.push_back(new LevelClearState(this));
    }
}

void Game::AwardPoints(unsigned value)
{
    points += value;

    log_info("[Game]\tScore changed to", points);
}

bool Game::IsPaused()
{
    for (std::list<GameState*>::iterator i = states.begin(); i != states.end(); ++i)
        if (dynamic_cast<GamePausedState*>(*i))
            return true;

    return false;
}

void Game::OnGameStateFinish(GameState* state)
{
    delete state;
    states.remove(state);
}

void Game::OnKill(Object* killer, Object* victim)
{
    if (dynamic_cast<Player*>(victim))
    {
        log_info("[Game]\tPlayer killed.");
        states.push_back(new GameOverState(this));
        return;
    }

    // award points based on object type
    if (dynamic_cast<Goomba*>(victim))
        AwardPoints(10);

    else if (dynamic_cast<Koopa*>(victim))
        AwardPoints(20);

    else if (dynamic_cast<Spiny*>(victim))
        AwardPoints(50);

    else if (dynamic_cast<Lakitu*>(victim))
        AwardPoints(100);
}

void Game::OnPlayerAddToMap(Player* player)
{
    this->player = player;

    log_info("[Map]\tPlayer added.");
}

void Game::OnObjectOutOfMap(Object* object)
{
    log_info("[Map]\tObject out of map.");

    if (dynamic_cast<Player*>(object))
    {
        this->player = nullptr;
        states.push_back(new GameOverState(this));
    }

    else if (dynamic_cast<Koopa*>(object))
        AwardPoints(20);
}
