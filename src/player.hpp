#ifndef __Player__
#define __Player__

#include "common.hpp"
#include "object.hpp"

namespace Mario
{
    struct Player : public Object
    {
        Player(size_t tile_x, size_t tile_y) : Object(tile_x, tile_y) {}
        ~Player() {}

        void OnKeyDown(int key);
        void OnKeyUp(int key);
    };
}

#endif
