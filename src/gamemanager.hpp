#ifndef __GameManager__
#define __GameManager__

#include "common.hpp"
#include "game.hpp"
#include "tilemanager.hpp"

namespace Mario
{
    struct GameManager
    {
        GameManager() : done(false) {}
        ~GameManager() {}

        void Init();
        void Loop();
        void Cleanup();
        void Update(float dt);
        void Draw();
        bool IsDone() { return done; }
        bool IsPaused() { return false; } //todo

        ALLEGRO_DISPLAY* display;
        ALLEGRO_EVENT_QUEUE* queue;
        ALLEGRO_TIMER* redraw_timer;
        ALLEGRO_TIMER* update_timer;
        Game* game;
        TileManager* tile_mgr;
        bool done;
        const float fps = 60;
        const float ups = 100;
        const size_t width = 1024;
        const size_t height = 768;
    };
}

#endif
