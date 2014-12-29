#ifndef __Map__
#define __Map__

#include "common.hpp"
#include "object.hpp"
#include "player.hpp"

namespace Mario
{
    typedef std::vector<Tile> TileRow;
    typedef std::vector<TileRow> TileSet;

    struct Map
    {
        Map(Game* game, std::string path);
        ~Map();

        void Load(std::string path);
        void Save(std::string path);
        void AddObject(Object* o);
        void AddPlayer(Player* p);
        void SpawnObjects();
        void Update(float dt);

        TileSet tiles;
        std::list<Object*> objs;
        Game* game;
        Player* player;
        bool edit_mode;
    };
}

#endif
