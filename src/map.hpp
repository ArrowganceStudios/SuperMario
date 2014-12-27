#ifndef __Map__
#define __Map__

#include "common.hpp"
#include "object.hpp"

namespace Mario
{
    const size_t TileSize = 32;

    enum Tile
    {
        TILE_EMPTY,

        TILE_GRASS,
        TILE_SAND,
        TILE_WALL,

        TILE_PLAYER_SPAWN,
        TILE_GOOMBA_SPAWN,
        TILE_KOOPA_SPAWN,
        TILE_SPINY_SPAWN,
        TILE_LAKITU_SPAWN,

        MAX_TILE
    };

    typedef std::vector<Tile> TileRow;
    typedef std::vector<TileRow> TileSet;

    struct Map
    {
        Map(std::string path);
        void load(std::string path);
        void save(std::string path);

        TileSet tiles;
        std::list<Object*> objs;
    };
}

#endif
