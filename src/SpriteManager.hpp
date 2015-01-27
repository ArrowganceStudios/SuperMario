/**
 * @file        SpriteManager.hpp
 * @author      mg6 (maciej@gamrat.it)
 * @date        2014-2015
 * @copyright   GNU GPL v2
 */

#ifndef __SpriteManager__
#define __SpriteManager__

#include "Common.hpp"
#include "ScreenHandler.hpp"
#include "Map.hpp"

namespace Mario
{
    /// Sprite info class
    struct SpriteInfo
    {
        /**
         * Sprite info constructor
         * @param path Sprite map file path.
         * @param tile_width Tile width.
         * @param tile_height Tile height.
         * @param row_size Count of tiles in row.
         */
        SpriteInfo(std::string path, size_t tile_width, size_t tile_height,
            size_t row_size) : path(path), tile_width(tile_width),
            tile_height(tile_height), row_size(row_size) {}

        ~SpriteInfo() {}

        std::string path;           ///< Sprite map file path
        size_t tile_width;          ///< Tile width
        size_t tile_height;         ///< Tile height
        size_t row_size;            ///< Count of tiles in row
    };

    /// Sprite manager class
    struct SpriteManager : public ScreenHandler
    {
        /// Object type to sprite info map type
        typedef std::map<ObjectType, SpriteInfo*> SpriteInfoMap;

        /// Sprite sheet path to to Allegro bitmap map type
        typedef std::map<std::string, ALLEGRO_BITMAP*> PathToBitmapMap;

        SpriteManager(ScreenHandler::Size width, ScreenHandler::Size height,
            ScreenHandler::P offset_x = 0, ScreenHandler::P offset_y = 0)
        {
            SetScreenSize(width, height);
            SetScreenOffset(offset_x, offset_y);

            Register();
            Load();

            log_info("[Spr]\tSprite manager initialized.");
        }

        ~SpriteManager();

        /**
         * Draws sprites on the map.
         * @param map Game map.
         */
        void Draw(Map* map);

        /**
         * Registers sprite map files.
         */
        void Register();

        /**
         * Loads sprite maps from disk.
         */
        void Load();

        PathToBitmapMap bitmaps;    ///< Loaded sprite bitmaps
        SpriteInfoMap sprites;      ///< Sprite information map
    };
}

#endif
