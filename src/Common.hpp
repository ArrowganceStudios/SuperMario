/**
 * @file        Common.hpp
 * @author      mg6 (maciej@gamrat.it)
 * @date        2014-2015
 * @copyright   GNU GPL v2
 */

#ifndef __Common__
#define __Common__

#include <iostream>
#include <fstream>
#include <list>
#include <map>
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

#define __DEBUG__   1               ///< Debug info display flag

#if __GNUC__
#   define ASSETS   "assets/"       ///< Asset path prefix
#else
#   define ASSETS   "assets\\"      ///< Asset path prefix
#endif

namespace Mario
{
#if __DEBUG__
    /// Prints log info (single arg).
    template <typename T>
    void log_info(T t)
    {
        std::cout << t << std::endl;
    }

    /// Prints log info (multiple args).
    template <typename T, typename... Args>
    void log_info(T t, Args... args)
    {
        std::cout << t << " ";
        log_info(args...);
    }
#else
#   define log_info(...)
#endif

    /// Prints log errors (single arg).
    template <typename T>
    void log_error(T t)
    {
        std::cerr << t << std::endl;
    }

    /// Prints log errors (multiple args).
    template <typename T, typename... Args>
    void log_error(T t, Args... args)
    {
        std::cerr << t << " ";
        log_error(args...);
    }

    const size_t TileSize = 32;             ///< Map tile size
    const float Gravity = 30 * TileSize;    ///< Gravity

    /**
     * Tile types
     *
     * Tiles between empty and player spawn tiles (exclusive) are solid,
     * so that objects can stand on them.
     */
    enum Tile
    {
        TILE_EMPTY,

        TILE_GRASS_LEFT,
        TILE_GRASS_MID,
        TILE_GRASS_RIGHT,
        TILE_SAND_LEFT,
        TILE_SAND_MID,
        TILE_SAND_RIGHT,
        TILE_WALL,

        TILE_PLAYER_SPAWN = 50,  ///< Player spawn tile
        TILE_GOOMBA_SPAWN,  ///< Goomba spawn tile
        TILE_KOOPA_SPAWN,   ///< Koopa spawn tile
        TILE_SPINY_SPAWN,   ///< Spiny spawn tile
        TILE_LAKITU_SPAWN,  ///< Lakitu spawn tile

        MAX_TILE_TYPE       = 500, ///< Max tile ID

        TILE_SOLID_START    = TILE_GRASS_LEFT,
        TILE_SOLID_END      = TILE_GRASS_RIGHT
    };

    /**
     * Map object type list
     *
     * Lists all possible map spawns.
     */
    enum ObjectType
    {
        OBJECT_UNKNOWN,     ///< Unknown spawn

        OBJECT_PLAYER,      ///< Player spawn
        OBJECT_GOOMBA,      ///< Goomba spawn
        OBJECT_KOOPA,       ///< Koopa spawn
        OBJECT_SPINY,       ///< Spiny spawn
        OBJECT_LAKITU,      ///< Lakitu spawn

        MAX_OBJECT_TYPE     ///< Max spawn type
    };

    /**
     * Map object state list
     *
     * These flags are stored in Object's state variable and hold movement
     * and animation information.
     */
    enum ObjectState
    {
        STATE_ALIVE     = (1 << 0),     ///< Alive flag
        STATE_RUN       = (1 << 1),     ///< Running flag
        STATE_LEFT      = (1 << 2),     ///< Moving left flag
        STATE_JUMP      = (1 << 3),     ///< Jumping flag
        STATE_FALL      = (1 << 4),     ///< Falling flag
        STATE_FLY       = (1 << 5),     ///< Flying object flag
    };

    /**
     * Key state flags
     *
     * Un/set by key press and release handlers.
     */
    enum KeyState
    {
        KEY_STATE_UP    = (1 << 0),
        KEY_STATE_DOWN  = (1 << 1),
        KEY_STATE_LEFT  = (1 << 2),
        KEY_STATE_RIGHT = (1 << 3),
        KEY_STATE_X     = (1 << 4),
    };

    struct Map;
    struct GameState;
    struct Game;
}

#endif
