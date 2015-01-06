/**
 * @file        SpriteManager.hpp
 * @author      mg6 (maciej@gamrat.it)
 * @date        2014-2015
 * @copyright   GNU GPL v2
 */

#ifndef __SpriteManager__
#define __SpriteManager__

#include "Common.hpp"
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

    /// Object type to sprite info map type
    typedef std::map<ObjectType, SpriteInfo*> SpriteInfoMap;

    /// Sprite sheet path to to Allegro bitmap map type
    typedef std::map<std::string, ALLEGRO_BITMAP*> PathToBitmapMap;

    /// Sprite manager class
    struct SpriteManager
    {
        SpriteManager()
        {
            Register();
            Load();
        }

        ~SpriteManager();

        /**
         * Draws sprites on the map.
         * @param map Game map.
         * @param height Screen height.
         */
        void Draw(Map* map, size_t height);

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
