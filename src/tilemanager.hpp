#ifndef __TileManager__
#define __TileManager__

#include "common.hpp"
#include "map.hpp"

namespace Mario
{
    struct TileManager
    {
        TileManager() {}
        ~TileManager() {}

        ALLEGRO_COLOR GetTileColor(Map* map, Tile& tile);
        void DrawMap(size_t height, Map* map);
    };
}

#endif
