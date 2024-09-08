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
#include "SplashScreenManager.hpp"

namespace Mario
{
    /// Game manager class.
    struct GameManager
    {
        GameManager() throw() : display(nullptr), queue(nullptr),
            redraw_timer(nullptr), update_timer(nullptr), game(nullptr),
            sprite_mgr(nullptr), tile_mgr(nullptr), done(false), font(nullptr) {}

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
         * Displays text on screen.
         * @param x X coordinate.
         * @param y Y coordinate.
         * @param col Color.
         * @param flags Align flags.
         * @param str String to print.
         */
        template <int o = 2, unsigned bg = 0x222222>
        void PutString(ScreenHandler::P x, ScreenHandler::P y, ScreenHandler::Color col, int flags, const char* str)
        {
            al_draw_text(font, ScreenHandler::toColor(bg), x+o, y+o, flags, str);
            al_draw_text(font, ScreenHandler::toColor(col), x, y, flags, str);
        }

        /**
         * Displays text on screen.
         * @param x X coordinate.
         * @param y Y coordinate.
         * @param col Color.
         * @param flags Align flags.
         * @param fmt String format.
         * @param val String parameter.
         */
        template <int o = 2, unsigned bg = 0x222222, typename T>
        void PutString(ScreenHandler::P x, ScreenHandler::P y, ScreenHandler::Color col, int flags, const char* fmt, T val)
        {
            al_draw_textf(font, ScreenHandler::toColor(bg), x+o, y+o, flags, fmt, val);
            al_draw_textf(font, ScreenHandler::toColor(col), x, y, flags, fmt, val);
        }

        /**
         * Returns true if main loop should finish.
         */
        bool IsDone() { return done; }

        ALLEGRO_DISPLAY* display;       ///< Screen display
        ALLEGRO_EVENT_QUEUE* queue;     ///< Event queue
        ALLEGRO_FONT* font;             ///< Display font
        ALLEGRO_TIMER* redraw_timer;    ///< Redraw timer
        ALLEGRO_TIMER* update_timer;    ///< Update timer
        Game* game;                     ///< Game object
        SplashScreenManager* splash_mgr;    ///< Splash screen handler
        SpriteManager* sprite_mgr;      ///< Sprite manager
        TileManager* tile_mgr;          ///< Tile manager
        bool done;                      ///< Done flag

        const size_t width = 640;       ///< Reference window width
        const size_t height = 480;      ///< Reference window height
        const float fps = 60;           ///< FPS setting
        const float ups = 100;          ///< Update frequency setting
    };

    /**
     * Joystick key identifiers.
     */
    enum JoyKeys
    {
        JOY_KEY_A       = 0,
        JOY_KEY_LB      = 4,
        JOY_KEY_RB      = 5,
        JOY_KEY_START   = 7,
    };

    /**
     * Joystick axis identifiers.
     */
    enum JoyAxis
    {
        JOY_AXIS_X      = 0,
        JOY_AXIS_Y      = 1,
        JOY_AXIS_Z      = 2,
    };
}

#endif
