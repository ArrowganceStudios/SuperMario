#include "game.hpp"

using namespace Mario;

Game::Game()
{
    map = new Map("level1.txt");
    player = new Player();

    LOG("Game created.");
}

Game::~Game()
{
    delete player;
    delete map;

    LOG("Game destroyed.");
}

void Game::load_map(std::string path)
{
    map->load(path);
}

void Game::save_map(std::string path)
{
    map->save(path);
}
