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

    for (PathToBitmapMap::iterator i = bitmaps.begin(); i != bitmaps.end(); ++i)
    {
        al_destroy_bitmap(i->second);
        log_info("[Spr]\tUnloaded sprite sheet", i->first);
    }
}

void SpriteManager::Register()
{
    sprites[OBJECT_PLAYER]  = new SpriteInfo(ASSETS "mario.png", 30, 40, 15);
    sprites[OBJECT_GOOMBA]  = new SpriteInfo(ASSETS "goomba.png", 22, 26, 7);
    sprites[OBJECT_KOOPA]   = new SpriteInfo(ASSETS "koopa.png", 16, 28, 8);
    sprites[OBJECT_LAKITU]  = new SpriteInfo(ASSETS "enemies.png", 16, 32, 4);
    sprites[OBJECT_SPINY]   = new SpriteInfo(ASSETS "spiny.png", 16, 16, 4);
}

void SpriteManager::Load()
{
    for (SpriteInfoMap::iterator i = sprites.begin(); i != sprites.end(); ++i)
        if (!bitmaps[i->second->path])
        {
            if (bitmaps[i->second->path] = al_load_bitmap(i->second->path.c_str()))
                log_info("[Spr]\tLoaded sprite sheet", i->second->path);
            else
                log_error("[Spr]\tCould not load sprite sheet", i->second->path);
        }
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

        al_draw_scaled_bitmap(bitmaps[info->path],
            tile % info->row_size * info->tile_width,
            tile / info->row_size * info->tile_height,
            info->tile_width, info->tile_height,
            o->pos_x-info->tile_width - map->offset,
            height-(o->pos_y+info->tile_height*2),
            2*info->tile_width, 2*info->tile_height,
            0);
    }
}
