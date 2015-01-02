#include "map.hpp"
#include "spritemanager.hpp"

using namespace Mario;

void SpriteManager::Draw(Map* map, size_t height)
{
    for (std::list<Object*>::iterator obj = map->objs.begin(); obj != map->objs.end(); ++obj)
        (*obj)->OnDraw(height);
}
