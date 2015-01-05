/**
 * @file        TileManager.hpp
 * @author      mg6 (maciej@gamrat.it)
 * @date        2014-2015
 * @copyright   GNU GPL v2
 */

#ifndef __TileManager__
#define __TileManager__

#include "Common.hpp"
#include "Map.hpp"

namespace Mario
{
    /// Tile manager class.
    struct TileManager
    {
        TileManager() : tiles(nullptr)
        {
            if (tiles = al_load_bitmap(ASSETS "tiles.png"))
                log_info("[Tile]\tTiles loaded.");
            else
                log_error("[Tile]\tCould not load tiles.");
        }

        ~TileManager()
        {
            al_destroy_bitmap(tiles);
        }

        /**
         * Returns tile color based on tile type.
         * @param map Game map.
         * @param tile Tile type.
         */
        static ALLEGRO_COLOR GetTileColor(Map* map, Tile& tile);

        /**
         * Returns tile sheet index for specified tile type.
         * @param tile Tile type.
         */
        unsigned GetTileIndex(Tile tile);

        /**
         * Draws the map on screen.
         * @param map Game map.
         * @param height Screen height.
         */
        void Draw(Map* map, size_t height);

        ALLEGRO_BITMAP* tiles;      ///< Tile sheet
    };
}

#endif
