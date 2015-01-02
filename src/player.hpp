#ifndef __Player__
#define __Player__

#include "common.hpp"
#include "object.hpp"

namespace Mario
{
    /// Player class.
    struct Player : public Object
    {
        /**
         * Player constructor.
         * @param tile_x X map tile.
         * @param tile_y Y map tile.
         */
        Player(Map* map, size_t tile_x, size_t tile_y) : Object(map, tile_x, tile_y) {}

        ~Player() {}

        /**
         * Key down handler.
         * @param key Pressed key.
         */
        void OnKeyDown(int key);

        /**
         * Key up handler.
         * @param key Released key.
         */
        void OnKeyUp(int key);
    };
}

#endif
