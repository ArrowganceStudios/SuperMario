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

        ALLEGRO_COLOR get_tile_color(Tile& tile);
        void draw_map(size_t height, Map* map);
    };
}

#endif
