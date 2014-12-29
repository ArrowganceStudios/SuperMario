#ifndef __Object__
#define __Object__

#include "common.hpp"

namespace Mario
{
    struct Object
    {
        Object(size_t tile_x, size_t tile_y)
        {
            pos_x = TileSize * tile_x + size_x/2;
            pos_y = TileSize * tile_y;
        }

        virtual void OnUpdate(float dt);
        virtual void OnDraw();

        float pos_x; // map coords
        float pos_y;
        float dir_x; // x direction
        const float size_x = TileSize;
    };

    struct Enemy : public Object
    {
        Enemy(size_t tile_x, size_t tile_y) : Object(tile_x, tile_y) {}
    };

    struct Goomba : public Enemy
    {
        Goomba(size_t tile_x, size_t tile_y) : Enemy(tile_x, tile_y) {}
    };

    struct Koopa : public Enemy
    {
        Koopa(size_t tile_x, size_t tile_y) : Enemy(tile_x, tile_y) {}
    };

    struct Lakitu : public Enemy
    {
        Lakitu(size_t tile_x, size_t tile_y) : Enemy(tile_x, tile_y) {}
    };

    struct Spiny : public Enemy
    {
        Spiny(size_t tile_x, size_t tile_y) : Enemy(tile_x, tile_y) {}
    };
}

#endif
