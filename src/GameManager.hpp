/**
 * @file        GameManager.hpp
 * @author      mg6 (maciej@gamrat.it)
 * @date        2014-2015
 * @copyright   GNU GPL v2
 */

#ifndef __GameManager__
#define __GameManager__

#include "Common.hpp"
#include "Game.hpp"
#include "TileManager.hpp"
#include "SpriteManager.hpp"

namespace Mario
{
    /// Game manager class.
    struct GameManager
    {
        GameManager() throw() : display(nullptr), queue(nullptr), redraw_timer(nullptr),
            update_timer(nullptr), game(nullptr), sprite_mgr(nullptr), done(false) {}

        ~GameManager() {}

        /**
         * Initialize handler.
         */
        void Init();

        /**
         * Enters game loop.
         */
        void Loop();

        /**
         * Cleanup handler.
         */
        void Cleanup();

        /**
         * Game update handler.
         * @param dt Time increment.
         */
        void Update(float dt);

        /**
         * Draw handler.
         */
        void Draw();

        /**
         * Returns game time. Wrapper function.
         */
        inline static double GetTime()
        {
            return al_get_time();
        }

        /**
         * Returns true if main loop should finish.
         */
        bool IsDone() { return done; }

        ALLEGRO_DISPLAY* display;       ///< Screen display
        ALLEGRO_EVENT_QUEUE* queue;     ///< Event queue
        ALLEGRO_TIMER* redraw_timer;    ///< Redraw timer
        ALLEGRO_TIMER* update_timer;    ///< Update timer
        Game* game;                     ///< Game object
        SpriteManager* sprite_mgr;      ///< Sprite manager
        TileManager* tile_mgr;          ///< Tile manager
        bool done;                      ///< Done flag

        const size_t width = 640;       ///< Reference window width
        const size_t height = 480;      ///< Reference window height
        const float fps = 60;           ///< FPS setting
        const float ups = 100;          ///< Update frequency setting
    };
}

#endif
