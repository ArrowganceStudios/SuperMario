#include "map.hpp"
#include "game.hpp"

using namespace Mario;

Map::Map(Game* game, std::string path)
{
    this->game = game;
    this->player = nullptr;
    this->edit_mode = false;

    Load(path);
    SpawnObjects();

    log_info("[Map]\tCreated.");
}

Map::~Map()
{
    delete player;

    log_info("[Map]\tDeleted.");
}

void Map::Load(std::string path)
{
    tiles.clear();

    std::fstream file(path, std::ios::in);
    std::string line;

    while (true)
    {
        std::getline(file, line);

        if (file.eof())
            break;

        unsigned raw;
        TileRow row;
        std::stringstream row_stream(line);

        while (row_stream >> raw)
            row.push_back(Tile(raw));

        tiles.push_back(row);
    }

    file.close();
    log_info("[Map]\tLoaded.");
}

void Map::Save(std::string path)
{
    std::fstream file(path, std::ios::out);

    for (TileSet::iterator c = tiles.begin(); c != tiles.end(); ++c)
    {
        for (TileRow::iterator r = c->begin(); r != c->end(); ++r)
            file << Tile(*r) << " ";

        file << std::endl;
    }

    file.close();
    log_info("[Map]\tSaved.");
}

void Map::AddObject(Object* o)
{
    objs.push_back(o);

    game->OnObjectAddToMap(o);
}

void Map::AddPlayer(Player* p)
{
    objs.push_back(p);

    game->OnPlayerAddToMap(p);
}

void Map::SpawnObjects()
{
    for (size_t x = 0; x < tiles.size(); ++x)
        for (size_t y = 0; y < tiles[x].size(); ++y)
            switch (tiles[x][y])
            {
                case TILE_PLAYER_SPAWN:
                    AddPlayer(new Player(x, y));
                    break;

                case TILE_GOOMBA_SPAWN:
                    AddObject(new Goomba(x, y));
                    break;

                case TILE_KOOPA_SPAWN:
                    AddObject(new Koopa(x, y));
                    break;

                case TILE_LAKITU_SPAWN:
                    AddObject(new Lakitu(x, y));
                    break;

                case TILE_SPINY_SPAWN:
                    AddObject(new Spiny(x, y));
                    break;
            }
}

void Map::Update(float dt)
{
    for (std::list<Object*>::iterator i = objs.begin(); i != objs.end(); ++i)
        (*i)->OnUpdate(dt);
}
