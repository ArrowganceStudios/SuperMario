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
#include "SpriteManager.hpp"
#include "TileManager.hpp"
#include "GameManager.hpp"

namespace Mario
{
    struct SplashPlayer : public Player
    {
        SplashPlayer(Map* map, size_t tile_x, size_t tile_y) : Player(map, tile_x, tile_y) {}

        void OnUpdate(float dt);
    };

    struct SplashScreenManager : public Game
    {
        SplashScreenManager(GameManager* owner, SpriteManager* sprite_mgr, TileManager* tile_mgr);
        ~SplashScreenManager();

        void Draw();
        void Update(float dt);

        void OnObjectOutOfMap(Object* object);
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
