#ifndef __Common__
#define __Common__

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>
#include <cmath>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

namespace Mario
{
    template <typename T>
    void log_info(T t)
    {
        std::cout << t << std::endl;
    }

    template <typename T, typename... Args>
    void log_info(T t, Args... args)
    {
        std::cout << t << " ";
        log_info(args...);
    }

    const size_t TileSize = 32;

    enum Tile //< Tile types.
    {
        TILE_EMPTY,

        TILE_GRASS,
        TILE_SAND,
        TILE_WALL,

        TILE_PLAYER_SPAWN,
        TILE_GOOMBA_SPAWN,
        TILE_KOOPA_SPAWN,
        TILE_SPINY_SPAWN,
        TILE_LAKITU_SPAWN,

        MAX_TILE
    };

    struct Game;
}

#endif
