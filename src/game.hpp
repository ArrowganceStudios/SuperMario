#ifndef __Game__
#define __Game__

#include "common.hpp"
#include "object.hpp"
#include "player.hpp"
#include "map.hpp"

namespace Mario
{
    struct Game
    {
        Game();
        ~Game();

        // utilities

        void LoadMap(std::string path);
        void SaveMap(std::string path);
        void Update(float dt);

        // hooks

        void OnPlayerAddToMap(Player* player);
        void OnObjectAddToMap(Object* object);

        // properties

        Map* map;
        Player* player;
    };
}

#endif
