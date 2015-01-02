#ifndef __Objects__
#define __Objects__

#include "Common.hpp"

namespace Mario
{
    /// Generic map object.
    struct Object
    {
        /**
         * @param map Owner map.
         * @param tile_x X map tile.
         * @param tile_y Y map tile.
         */
        Object(Map* map, size_t tile_x, size_t tile_y) : dir_x(0), dir_y(0),
            falling(false), map(map), size_x(TileSize), state(STATE_ALIVE)
        {
            pos_x = TileSize * tile_x + size_x/2;
            pos_y = TileSize * tile_y;
        }

        /**
         * Kills an enemy.
         * @param enemy Enemy.
         */
        void Kill(Object* enemy);

        /**
         * Collision handler.
         * @param spawn Map spawn.
         */
        virtual void OnCollision(Object* spawn) {}

        /**
         * Update handler.
         * @param dt Time increment.
         */
        virtual void OnUpdate(float dt);

        /**
         * Draw handler.
         */
        virtual void OnDraw(size_t height);

        bool falling;       ///< Falling flag
        float pos_x;        ///< X map position
        float pos_y;        ///< Y map position
        float dir_x;        ///< Horizontal direction of movement
        float dir_y;        ///< Vertical direction of movement
        const float size_x; ///< Object size
        Map* map;           ///< Owner map
        ObjectState state;  ///< Alive state
    };

    /// Generic enemy class.
    struct Enemy : public Object
    {
        /// @copydoc Object
        Enemy(Map* map, size_t tile_x, size_t tile_y) : Object(map, tile_x, tile_y)
        {
            dir_x = (rand() % 2 == 0 ? 1 : -1) * 20;
        }

        void OnCollision(Object* spawn);
        void OnUpdate(float dt);
    };

    /// Goomba spawn.
    struct Goomba : public Enemy
    {
        /// @copydoc Enemy
        Goomba(Map* map, size_t tile_x, size_t tile_y) : Enemy(map, tile_x, tile_y) {}
    };

    /// Koopa spawn.
    struct Koopa : public Enemy
    {
        /// @copydoc Enemy
        Koopa(Map* map, size_t tile_x, size_t tile_y) : Enemy(map, tile_x, tile_y) {}
    };

    /// Lakitu spawn.
    struct Lakitu : public Enemy
    {
        /// @copydoc Enemy
        Lakitu(Map* map, size_t tile_x, size_t tile_y) : Enemy(map, tile_x, tile_y) {}
    };

    /// Spiny spawn.
    struct Spiny : public Enemy
    {
        /// @copydoc Enemy
        Spiny(Map* map, size_t tile_x, size_t tile_y) : Enemy(map, tile_x, tile_y) {}
    };
}

#endif
