#ifndef __TileManager__
#define __TileManager__

#include "common.hpp"
#include "map.hpp"

namespace Mario
{
    /// Tile manager class.
    struct TileManager
    {
        /**
         * Returns tile color based on tile type.
         * @param map Game map.
         * @param tile Tile type.
         */
        static ALLEGRO_COLOR GetTileColor(Map* map, Tile& tile);

        /**
         * Draws the map on screen.
         * @param map Game map.
         * @param height Screen height.
         */
        static void Draw(Map* map, size_t height);
    };
}

#endif
