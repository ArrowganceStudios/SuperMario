#ifndef __SpriteManager__
#define __SpriteManager__

#include "Common.hpp"
#include "Map.hpp"

namespace Mario
{
    /// Sprite manager class
    struct SpriteManager
    {
        /**
         * Draws sprites on the map.
         * @param map Game map.
         * @param height Screen height.
         */
        static void Draw(Map* map, size_t height);
    };
}

#endif
