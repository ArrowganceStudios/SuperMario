#ifndef __Game__
#define __Game__

#include "common.hpp"
#include "player.hpp"
#include "map.hpp"

namespace Mario
{
    struct Game
    {
        Game();
        ~Game();

        void load_map(std::string path);
        void save_map(std::string path);

        Map* map;
        Player* player;
    };
}

#endif
