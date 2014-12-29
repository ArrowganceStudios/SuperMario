#ifndef __Object__
#define __Object__

#include "common.hpp"

namespace Mario
{
    /// Generic map object.
    struct Object
    {
        /**
         * @param tile_x X map tile.
         * @param tile_y Y map tile.
         */
        Object(size_t tile_x, size_t tile_y)
        {
            pos_x = TileSize * tile_x + size_x/2;
            pos_y = TileSize * tile_y;
        }

        /**
         * Update handler.
         * @param dt Time increment.
         */
        virtual void OnUpdate(float dt);

        /**
         * Draw handler.
         */
        virtual void OnDraw();

        float pos_x;    ///< X map position.
        float pos_y;    ///< Y map position.
        float dir_x;    ///< Horizontal direction of movement.
        const float size_x = TileSize;  ///< Object size.
    };

    /// Generic enemy class.
    struct Enemy : public Object
    {
        /// @copydoc Object
        Enemy(size_t tile_x, size_t tile_y) : Object(tile_x, tile_y) {}
    };

    /// Goomba spawn.
    struct Goomba : public Enemy
    {
        /// @copydoc Enemy
        Goomba(size_t tile_x, size_t tile_y) : Enemy(tile_x, tile_y) {}
    };

    /// Koopa spawn.
    struct Koopa : public Enemy
    {
        /// @copydoc Enemy
        Koopa(size_t tile_x, size_t tile_y) : Enemy(tile_x, tile_y) {}
    };

    /// Lakitu spawn.
    struct Lakitu : public Enemy
    {
        /// @copydoc Enemy
        Lakitu(size_t tile_x, size_t tile_y) : Enemy(tile_x, tile_y) {}
    };

    /// Spiny spawn.
    struct Spiny : public Enemy
    {
        /// @copydoc Enemy
        Spiny(size_t tile_x, size_t tile_y) : Enemy(tile_x, tile_y) {}
    };
}

#endif
