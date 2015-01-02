#ifndef __Game__
#define __Game__

#include "common.hpp"
#include "object.hpp"
#include "player.hpp"
#include "map.hpp"

namespace Mario
{
    /// Game class.
    struct Game
    {
        Game();
        ~Game();

        /**
         * Loads map from file.
         * @param path Map file path.
         */
        void LoadMap(std::string path);

        /**
         * Saves map to file.
         * @param path Map file path.
         */
        void SaveMap(std::string path);

        /**
         * Game update handler.
         * @param dt Time increment.
         */
        void Update(float dt);

        /**
         * Called when an object kills another object.
         * @param killer Killer.
         * @param victim Victim.
         */
        void OnKill(Object* killer, Object* victim);

        /**
         * Called when player is added to map.
         * @param player Player.
         */
        void OnPlayerAddToMap(Player* player);

        /**
         * Called when object is added to map (except player).
         * @param object Object.
         */
        void OnObjectAddToMap(Object* object);

        Map* map;           ///< Game map
        Player* player;     ///< Player object
    };
}

#endif
