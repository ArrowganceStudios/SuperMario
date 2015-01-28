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
        /**
         * @param width Screen width.
         * @param height Screen height.
         * @param offset_x X offset.
         * @param offset_y Y offset.
         */
        TileManager(ScreenHandler::Size width, ScreenHandler::Size height,
            ScreenHandler::P offset_x = 0, ScreenHandler::P offset_y = 0) :
            tiles(nullptr), bg(nullptr)
        {
            SetScreenSize(width, height);
            SetScreenOffset(offset_x, offset_y);

            if (!(tiles = LoadBitmap(ASSETS "tiles.png")))
                throw std::runtime_error("[Tile] Could not load tiles.");

            if (!(bg = LoadBitmap(ASSETS "bg.png")))
                throw std::runtime_error("[Tile] Could not load background.");

            log_info("[Tile]\tTile manager initialized.");
        }

        ~TileManager()
        {
            if (tiles)
                DestroyBitmap(tiles);

            if (bg)
                DestroyBitmap(bg);

            log_info("[Tile]\tTile manager destroyed.");
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
         * @param bg Optional background bitmap.
         */
        void Draw(Map* map, ALLEGRO_BITMAP* bg = nullptr);

        ALLEGRO_BITMAP* tiles;      ///< Tile sheet
        ALLEGRO_BITMAP* bg;         ///< Map background
    };
}

#endif
