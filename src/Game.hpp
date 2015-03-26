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
        Game(GameManager* owner);
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
         * Starts the game.
         */
        void Start();

        /**
         * Game update handler.
         * @param dt Time increment.
         */
        void Update(float dt);

        /**
         * Awards points.
         * @param value Points.
         */
        void AwardPoints(unsigned value);

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
        virtual void OnKill(Object* killer, Object* victim);

        /**
         * Called when player is added to map.
         * @param player Player.
         */
        void OnPlayerAddToMap(Player* player);

        /**
         * Called when object is added to map (except player).
         * @param object Object.
         */
        void OnObjectAddToMap(Object* object) {}

        /**
         * Called when object falls out of map boundaries.
         * @param object Map object.
         */
        virtual void OnObjectOutOfMap(Object* object);

        GameManager* owner;             ///< Game manager owner
        Map* map;                       ///< Game map
        Player* player;                 ///< Player object
        std::list<GameState*> states;   ///< Game states
        bool done;                      ///< Game finished flag
        unsigned num_lives;             ///< Player life counter
        unsigned points;                ///< Player score
    };
}

#endif
