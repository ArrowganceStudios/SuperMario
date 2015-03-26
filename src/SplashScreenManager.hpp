/**
 * @file        SplashScreenManager.hpp
 * @author      mg6 (maciej@gamrat.it)
 * @date        2014-2015
 * @copyright   GNU GPL v2
 */

#ifndef __SplashScreenManager__
#define __SplashScreenManager__

#include "Common.hpp"
#include "ScreenHandler.hpp"
#include "Map.hpp"
#include "SoundManager.hpp"
#include "SpriteManager.hpp"
#include "TileManager.hpp"
#include "GameManager.hpp"

namespace Mario
{
    /**
     * Main menu player class.
     */
    struct SplashPlayer : public Player
    {
        /// @copydoc Player::Player
        SplashPlayer(Map* map, size_t tile_x, size_t tile_y) : Player(map, tile_x, tile_y) {}

        void OnUpdate(float dt);
    };

    /**
     * Splash screen manager class. Does main menu handling.
     */
    struct SplashScreenManager : public Game
    {
        /**
         * @param owner Game manager owner.
         * @param sprite_mgr Sprite manager to use.
         * @param tile_mgr Tile manager to use.
         */
        SplashScreenManager(GameManager* owner, SpriteManager* sprite_mgr, TileManager* tile_mgr);
        ~SplashScreenManager();

        /**
         * Draw handler.
         */
        void Draw();

        /**
         * Update handler.
         * @param dt Time increment.
         */
        void Update(float dt);

        /// @copydoc Game::OnObjectOutOfMap
        void OnObjectOutOfMap(Object* object);

        /// @copydoc Game::OnKill
        void OnKill(Object* killer, Object* victim) {} // do nothing, no points or game over

        Map* map;                   ///< Map to be drawn
        Player* player;             ///< Splash screen player
        SpriteManager* sprite_mgr;  ///< Sprite manager
        TileManager* tile_mgr;      ///< Tile manager
        GameManager* owner;         ///< Owner object
        ALLEGRO_BITMAP* logo;       ///< Game logo
        ALLEGRO_BITMAP* splash;     ///< Main menu background
    };
}

#endif
