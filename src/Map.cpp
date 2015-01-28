/**
 * @file        Map.cpp
 * @author      mg6 (maciej@gamrat.it)
 * @date        2014-2015
 * @copyright   GNU GPL v2
 */

#include "Map.hpp"
#include "Game.hpp"
#include "GameManager.hpp"

using namespace Mario;

Map::Map(Game* game, std::string path)
{
    log_info("[Map]\tCreated.");

    this->game = game;
    this->player = nullptr;
    this->edit_mode = false;
    this->offset = 0;

    Load(path);
    SpawnObjects();
}

Map::~Map()
{
    player = nullptr;

    for (Object* o : objs)
        delete o;

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

    if (game)
        game->OnObjectAddToMap(o);
}

void Map::AddPlayer(Player* p)
{
    objs.push_back(p);

    if (game)
        game->OnPlayerAddToMap(p);
}

void Map::SpawnObjects()
{
    for (size_t x = 0; x < tiles.size(); ++x)
        for (size_t y = 0; y < tiles[x].size(); ++y)
            switch (tiles[x][y])
            {
                case TILE_PLAYER_SPAWN:
                    AddPlayer(new Player(this, x, y));
                    break;

                case TILE_GOOMBA_SPAWN:
                    AddObject(new Goomba(this, x, y));
                    break;

                case TILE_KOOPA_SPAWN:
                    AddObject(new Koopa(this, x, y));
                    break;

                case TILE_LAKITU_SPAWN:
                    AddObject(new Lakitu(this, x, y));
                    break;

                case TILE_SPINY_SPAWN:
                    AddObject(new Spiny(this, x, y));
                    break;
            }
}

Player* Map::GetPlayer()
{
    for (ObjectList::iterator i = objs.begin(); i != objs.end(); ++i)
        if (Player* player = dynamic_cast<Player*>(*i))
            return player;

    return nullptr;
}

Tile Map::GetTile(int tile_x, int tile_y)
{
    if (tile_x < 0 || tile_y < 0 ||
        size_t(tile_x) >= tiles.size() ||
        size_t(tile_y) >= tiles[size_t(tile_x)].size())
        return TILE_EMPTY;

    return Tile(tiles[size_t(tile_x)][size_t(tile_y)]);
}

Tile Map::GetTileAtPos(float x, float y)
{
    return GetTile(ToTile(x), ToTile(y));
}

void Map::Update(float dt)
{
    for (ObjectList::iterator i = objs.begin(); i != objs.end(); )
    {
        // check if out of map
        if (IsObjectOutOfMap(*i))
        {
            if (game)
                game->OnObjectOutOfMap(*i);

            ObjectList::iterator out_of_map = i;
            ++i;

            if (Player* player = dynamic_cast<Player*>(*out_of_map))
                this->player = nullptr;

            delete *out_of_map;
            objs.remove(*out_of_map);

            continue;
        }

        // update object
        (*i)->OnUpdate(dt);

        // if falling and will land on solid tile in next frame
        if ((*i)->state & STATE_FALL && (*i)->state & STATE_ALIVE && (*i)->dir_y < 0 &&
            IsSolidTile( GetTileAtPos((*i)->pos_x + (*i)->dir_x * dt, (*i)->pos_y + (*i)->dir_y * dt) ))
        {
            // finish jump or fall
            (*i)->state &= ~(STATE_FALL | STATE_JUMP);
            (*i)->dir_y = 0;

            // place on top of tile
            (*i)->pos_y = Map::ToTile((*i)->pos_y + TileSize/2) * TileSize;

            // prevent running after jumping
            if (!((*i)->state & STATE_RUN))
                (*i)->dir_x = 0;

            if (Player* player = dynamic_cast<Player*>(*i))
                if (!(player->keys_down & KEY_STATE_X))
                    (*i)->dir_x_boost = 1.0f;
        }

        // if is not falling and is standing on non-solid tile
        else if (!((*i)->state & (STATE_FALL | STATE_FLY)) &&
            !IsSolidTile(GetTileAtPos((*i)->pos_x, (*i)->pos_y + (*i)->dir_y * dt - 1)))
            // begin falling
            (*i)->state |= STATE_FALL;

        // check collisions between alive objects
        ObjectList::iterator j = i;
        for (++j; j != objs.end(); ++j)
        {
            if (fabs((*i)->pos_x - (*j)->pos_x) < (*i)->size_x/2 + (*j)->size_x/2 &&
                fabs((*i)->pos_y - (*j)->pos_y) < (*j)->size_x/2 + (*j)->size_x/2)
            {
                if ((*i)->state & STATE_ALIVE && GameManager::GetTime() - (*i)->last_collision >= COLLISION_INTERVAL)
                {
                    (*i)->OnCollision(*j);
                    (*i)->last_collision = GameManager::GetTime();
                }

                if ((*j)->state & STATE_ALIVE && GameManager::GetTime() - (*j)->last_collision >= COLLISION_INTERVAL)
                {
                    (*j)->OnCollision(*i);
                    (*j)->last_collision = GameManager::GetTime();
                }
            }
        }

        ++i;
    }
}
