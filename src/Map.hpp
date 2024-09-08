/**
 * @file        Map.hpp
 * @author      mg6 (maciej@gamrat.it)
 * @date        2014-2015
 * @copyright   GNU GPL v2
 */

#ifndef __Map__
#define __Map__

#include "Common.hpp"
#include "Objects.hpp"
#include "Player.hpp"

namespace Mario
{
    typedef std::vector<Tile> TileRow;          ///< Single tile row type
    typedef std::vector<TileRow> TileSet;       ///< Tile map type
    typedef std::list<Object*> ObjectList;      ///< Map object list type

    /// Game map class.
    struct Map
    {
        /**
         * Game map constructor.
         * @param game Owner game object.
         * @param path Map file path.
         */
        Map(Game* game, std::string path);

        ~Map();

        /**
         * Loads map from file.
         * @param path Map file path.
         */
        void Load(std::string path);

        /**
         * Saves map to file.
         * @param path Map file path.
         */
        void Save(std::string path);

        /**
         * Adds object to map.
         * @param object Object.
         */
        void AddObject(Object* object);

        /**
         * Adds player to map.
         * @param player Player.
         */
        void AddPlayer(Player* player);

        /** Spawns objects on map. */
        void SpawnObjects();

        /**
         * Map update handler.
         * @param dt Time increment.
         */
        void Update(float dt);

        /**
         * Returns map tile from coordinate.
         * @param pos X or Y coord.
         */
        inline static int ToTile(float pos)
        {
            return floor(pos/TileSize);
        }

        /**
         * Returns map width in pixels.
         */
        float GetMapWidth()
        {
            return tiles.size() * TileSize;
        }

        /**
         * Returns player from spawn list.
         */
        Player* GetPlayer();

        /**
         * Returns tile type at given map tile.
         * @param tile_x Map tile X.
         * @param tile_y Map tile Y.
         */
        Tile GetTile(int tile_x, int tile_y);

        /**
         * Returns tile type at given coordinates.
         * @param x X map coord.
         * @param y Y map coord.
         */
        Tile GetTileAtPos(float x, float y);

        /**
         * Returns true if object is out of map and should be deleted.
         * @param o Map object.
         */
        inline bool IsObjectOutOfMap(Object* o)
        {
            return o->pos_y < -3.0f * TileSize;
        }

        /**
         * Returns true if the tile is solid (it is possible to stand on it).
         * @param tile Tile type.
         */
        inline static bool IsSolidTile(Tile tile)
        {
            return tile >= TILE_SOLID_START && tile <= TILE_SOLID_END;
        }

        Game* game;                 ///< Game object
        Player* player;             ///< Player object
        TileSet tiles;              ///< Map tileset
        ObjectList objs;            ///< Object  list
        bool edit_mode;             ///< Edit mode flag
        float offset;               ///< Map offset
    };
}

#endif
