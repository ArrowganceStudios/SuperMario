#ifndef __TileManager__
#define __TileManager__

#include "common.hpp"
#include "map.hpp"

namespace Mario
{
    /// Tile manager class.
    struct TileManager
    {
        TileManager() {}
        ~TileManager() {}

        /**
         * Returns tile color based on tile type.
         * @param map Game map.
         * @param tile Tile type.
         */
        ALLEGRO_COLOR GetTileColor(Map* map, Tile& tile);

        /**
         * Draws the map on screen.
         * @param map Game map.
         * @param height Screen height.
         */
        void DrawMap(Map* map, size_t height);
    };
}

#endif
