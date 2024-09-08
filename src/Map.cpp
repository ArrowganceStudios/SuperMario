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

                default:
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
        Object* me = *i;

        // check if out of map
        if (IsObjectOutOfMap(me))
        {
            if (game)
                game->OnObjectOutOfMap(me);

            ObjectList::iterator out_of_map = i;
            ++i, me = *i;

            if (Player* player = dynamic_cast<Player*>(*out_of_map))
                this->player = nullptr;

            delete *out_of_map;
            objs.remove(*out_of_map);

            continue;
        }

        // update object
        me->OnUpdate(dt);

        // if falling and will land on solid tile in next frame
        if (me->IsFalling() && me->IsAlive() && me->dir_y < 0 &&
            IsSolidTile( GetTileAtPos(me->pos_x + me->dir_x * dt, me->pos_y + me->dir_y * dt) ))
        {
            // finish jump or fall
            me->ClearState(STATE_FALL);
            me->ClearState(STATE_JUMP);
            me->dir_y = 0;

            // place on top of tile
            me->pos_y = Map::ToTile(me->pos_y + TileSize/2) * TileSize;

            // prevent running after jumping
            if (!me->IsRunning())
                me->dir_x = 0;

            if (Player* player = dynamic_cast<Player*>(*i))
                if (!(player->keys_down & KEY_STATE_RUN))
                    me->dir_x_boost = 1.0f;
        }

        // if is not falling and is standing on non-solid tile
        else if (
            !me->IsFalling() && !me->IsFlying()
            && !IsSolidTile(GetTileAtPos(me->pos_x, me->pos_y + me->dir_y * dt - 1))
        )
        {
            // begin falling
            me->SetState(STATE_FALL);
        }

        // check collisions between alive objects
        ObjectList::iterator j = i;
        for (++j; j != objs.end(); ++j)
        {
            Object* them = *j;

            if (fabs(me->pos_x - them->pos_x) < me->size_x/2 + them->size_x/2 &&
                fabs(me->pos_y - them->pos_y) < them->size_x/2 + them->size_x/2)
            {
                if (me->IsAlive())
                {
                    me->OnCollision(them);
                }

                if (them->IsAlive())
                {
                    them->OnCollision(me);
                }
            }
        }

        ++i;
    }
}
