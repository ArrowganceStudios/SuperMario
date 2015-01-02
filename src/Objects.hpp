#ifndef __Objects__
#define __Objects__

#include "Common.hpp"

namespace Mario
{
    /// Generic map object.
    struct Object
    {
        /**
         * @param type Object type.
         * @param map Owner map.
         * @param tile_x X map tile.
         * @param tile_y Y map tile.
         */
        Object(ObjectType type, Map* map, size_t tile_x, size_t tile_y) :
            dir_x(0), dir_y(0), size_x(TileSize), map(map), state(STATE_ALIVE),
            type(type), frame(0), anim_timer(0)
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
         * Draw handler. Returns tile number to display by sprite manager.
         */
        virtual size_t OnDraw() { return 0; }

        float pos_x;        ///< X map position
        float pos_y;        ///< Y map position
        float dir_x;        ///< Horizontal direction of movement
        float dir_y;        ///< Vertical direction of movement
        float anim_timer;   ///< Animation timer
        unsigned frame;     ///< Current frame
        const float size_x; ///< Object size
        Map* map;           ///< Owner map
        unsigned state;     ///< Alive state
        ObjectType type;    ///< Object type
    };

    /// Generic enemy class.
    struct Enemy : public Object
    {
        /// @copydoc Object
        Enemy(ObjectType type, Map* map, size_t tile_x, size_t tile_y) :
            Object(type, map, tile_x, tile_y)
        {
            dir_x = (rand() % 2 == 0 ? 1 : -1) * 20;
        }

        void OnCollision(Object* spawn);
        void OnUpdate(float dt);
    };

    /// Goomba spawn.
    struct Goomba : public Enemy
    {
        /**
         * Goomba spawn constructor.
         * @param map Owner map.
         * @param tile_x X map tile.
         * @param tile_y Y map tile.
         */
        Goomba(Map* map, size_t tile_x, size_t tile_y) :
            Enemy(OBJECT_GOOMBA, map, tile_x, tile_y) {}
    };

    /// Koopa spawn.
    struct Koopa : public Enemy
    {
        /**
         * Koopa spawn constructor.
         * @param map Owner map.
         * @param tile_x X map tile.
         * @param tile_y Y map tile.
         */
        Koopa(Map* map, size_t tile_x, size_t tile_y) :
            Enemy(OBJECT_KOOPA, map, tile_x, tile_y) {}
    };

    /// Lakitu spawn.
    struct Lakitu : public Enemy
    {
        /**
         * Lakitu spawn constructor.
         * @param map Owner map.
         * @param tile_x X map tile.
         * @param tile_y Y map tile.
         */
        Lakitu(Map* map, size_t tile_x, size_t tile_y) :
            Enemy(OBJECT_LAKITU, map, tile_x, tile_y) {}
    };

    /// Spiny spawn.
    struct Spiny : public Enemy
    {
        /**
         * Spiny spawn constructor.
         * @param map Owner map.
         * @param tile_x X map tile.
         * @param tile_y Y map tile.
         */
        Spiny(Map* map, size_t tile_x, size_t tile_y) :
            Enemy(OBJECT_SPINY, map, tile_x, tile_y) {}
    };
}

#endif
