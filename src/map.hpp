#ifndef __Map__
#define __Map__

#include "common.hpp"
#include "object.hpp"
#include "player.hpp"

namespace Mario
{
    typedef std::vector<Tile> TileRow;
    typedef std::vector<TileRow> TileSet;

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

        Game* game;                 ///< Game object
        Player* player;             ///< Player object
        TileSet tiles;              ///< Map tileset
        std::list<Object*> objs;    ///< Object  list
        bool edit_mode;             ///< Edit mode flag
    };
}

#endif
