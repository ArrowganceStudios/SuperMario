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

#define __DEBUG__   1

namespace Mario
{
#if __DEBUG__
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
#else
#   define log_info(...)
#endif

    const size_t TileSize = 32; ///< Map tile size

    /**
     * Tile types.
     */
    enum Tile
    {
        TILE_EMPTY,         ///< Empty tile

        TILE_GRASS,         ///< Grass tile
        TILE_SAND,          ///< Sand tile
        TILE_WALL,          ///< Wall tile

        TILE_PLAYER_SPAWN,  ///< Player spawn tile
        TILE_GOOMBA_SPAWN,  ///< Goomba spawn tile
        TILE_KOOPA_SPAWN,   ///< Koopa spawn tile
        TILE_SPINY_SPAWN,   ///< Spiny spawn tile
        TILE_LAKITU_SPAWN,  ///< Lakitu spawn tile

        MAX_TILE            ///< Max tile ID
    };

    struct Game;
}

#endif
