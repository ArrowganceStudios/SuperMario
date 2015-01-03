/**
 * @file        SpriteManager.cpp
 * @author      mg6 (maciej@gamrat.it)
 * @date        2014-2015
 * @copyright   GNU GPL v2
 */

#include "Map.hpp"
#include "SpriteManager.hpp"

using namespace Mario;

SpriteManager::~SpriteManager()
{
    for (SpriteInfoMap::iterator i = sprites.begin(); i != sprites.end(); ++i)
        delete i->second;
}

void SpriteManager::Register()
{
    sprites[OBJECT_PLAYER] = new SpriteInfo(ASSETS "mario.png", 30, 40, 15);
}

void SpriteManager::Load()
{
    for (SpriteInfoMap::iterator i = sprites.begin(); i != sprites.end(); ++i)
        if (i->second->bitmap = al_load_bitmap(i->second->path.c_str()))
            log_info("[Spr]\tLoaded sprite sheet", i->second->path);
        else
            log_error("[Spr]\tCould not load sprite sheet", i->second->path);
}

void SpriteManager::Draw(Map* map, size_t height)
{
    for (ObjectList::iterator obj = map->objs.begin(); obj != map->objs.end(); ++obj)
    {
        Object* o = *obj;
        SpriteInfo* info = sprites[o->type];

        if (!info)
        {
            al_draw_filled_rectangle(o->pos_x-TileSize/2, height-o->pos_y,
                o->pos_x + TileSize/2, height-(o->pos_y + TileSize), al_map_rgb(255, 255, 255));
            continue;
        }

        size_t tile = o->OnDraw();

        al_draw_scaled_bitmap(info->bitmap,
            tile % info->row_size * info->tile_width,
            tile / info->row_size * info->tile_height,
            info->tile_width, info->tile_height,
            o->pos_x-info->tile_width,
            height-(o->pos_y+info->tile_height*2),
            2*info->tile_width, 2*info->tile_height,
            0);
    }
}
