#ifndef __Game__
#define __Game__

#include "common.hpp"
#include "map.hpp"

namespace Mario
{
    struct Game
    {
        Game() : map(nullptr) {}

        ~Game()
        {
            delete map;
        }

        Map* map;
    };
}

#endif

