/**
 * @file        TileManager.hpp
 * @author      mg6 (maciej@gamrat.it)
 * @date        2014-2015
 * @copyright   GNU GPL v2
 */

#ifndef __TileManager__
#define __TileManager__

#include "Common.hpp"
#include "ScreenHandler.hpp"
#include "Map.hpp"

namespace Mario
{
    /// Tile manager class.
    struct TileManager : public ScreenHandler
    {
        TileManager(ScreenHandler::Size width, ScreenHandler::Size height,
            ScreenHandler::P offset_x = 0, ScreenHandler::P offset_y = 0) : tiles(nullptr)
        {
            SetScreenSize(width, height);
            SetScreenOffset(offset_x, offset_y);

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
        static ScreenHandler::Color GetTileColor(Map* map, Tile& tile);

        /**
         * Returns tile sheet index for specified tile type.
         * @param tile Tile type.
         */
        unsigned GetTileIndex(Tile tile);

        /**
         * Draws the map on screen.
         * @param map Game map.
         */
        void Draw(Map* map);

        ALLEGRO_BITMAP* tiles;      ///< Tile sheet
    };
}

#endif
