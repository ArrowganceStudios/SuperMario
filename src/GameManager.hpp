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
        GameManager() : done(false) {}
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
         * Returns true if main loop should finish.
         */
        bool IsDone() { return done; }

        /**
         * Returns paused state.
         */
        bool IsPaused() { return false; } //todo

        ALLEGRO_DISPLAY* display;       ///< Screen display
        ALLEGRO_EVENT_QUEUE* queue;     ///< Event queue
        ALLEGRO_TIMER* redraw_timer;    ///< Redraw timer
        ALLEGRO_TIMER* update_timer;    ///< Update timer
        Game* game;                     ///< Game object
        bool done;                      ///< Done flag

        const float fps = 60;           ///< FPS setting
        const float ups = 100;          ///< Update frequency setting
        const size_t width = 1024;      ///< Window width
        const size_t height = 768;      ///< Window height
    };
}

#endif
