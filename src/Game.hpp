/**
 * @file        Game.hpp
 * @author      mg6 (maciej@gamrat.it)
 * @date        2014-2015
 * @copyright   GNU GPL v2
 */

#ifndef __Game__
#define __Game__

#include "Common.hpp"
#include "Objects.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "GameStates.hpp"
#include "SpriteManager.hpp"

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
         * Returns paused state flag.
         */
        bool IsPaused();

        /**
         * Called on game state begin.
         * @param state Game state.
         */
        void OnGameStateStart(GameState* state) {}

        /**
         * Called on game state finish.
         * @param state Game state.
         */
        void OnGameStateFinish(GameState* state);

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

        Map* map;                       ///< Game map
        Player* player;                 ///< Player object
        std::list<GameState*> states;   ///< Game states
        bool done;                      ///< Game finished flag
    };
}

#endif
