#include "game.hpp"

using namespace Mario;

Game::Game()
{
    map = new Map(this, ASSETS "map1");

    log_info("[Game]\tCreated.");
}

Game::~Game()
{
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
    map->Update(dt);
}

void Game::OnPlayerAddToMap(Player* player)
{
    this->player = player;

    log_info("[Game]\tPlayer added.");
};

void Game::OnObjectAddToMap(Object* object)
{
    log_info("[Game]\tObject added.");
}
