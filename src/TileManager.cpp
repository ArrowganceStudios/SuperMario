/**
 * @file        TileManager.cpp
 * @author      mg6 (maciej@gamrat.it)
 * @date        2014-2015
 * @copyright   GNU GPL v2
 */

#include "Map.hpp"
#include "TileManager.hpp"

using namespace Mario;

ScreenHandler::Color TileManager::GetTileColor(Map* map, Tile& tile)
{
    /*
    switch (tile)
    {
        case TILE_EMPTY:
            return MakeCol(0, 127, 255);

        case TILE_GRASS:
            return MakeCol(0, 255, 0);

        case TILE_SAND:
            return MakeCol(255, 255, 127);

        case TILE_WALL:
            return MakeCol(255, 127, 0);
    }
    */

    if (map->edit_mode)
        switch (tile)
        {
            case TILE_PLAYER_SPAWN:
                return MakeCol(255, 0, 0);

            case TILE_GOOMBA_SPAWN:
                return MakeCol(255, 0, 0);

            case TILE_KOOPA_SPAWN:
                return MakeCol(255, 255, 0);

            case TILE_LAKITU_SPAWN:
                return MakeCol(127, 0, 255);

            case TILE_SPINY_SPAWN:
                return MakeCol(255, 0, 127);
        }
    else
        switch (tile)
        {
            case TILE_PLAYER_SPAWN:
            case TILE_GOOMBA_SPAWN:
            case TILE_KOOPA_SPAWN:
            case TILE_LAKITU_SPAWN:
            case TILE_SPINY_SPAWN:
                return MakeCol(0, 127, 255);
        }

    return MakeCol(0, 0, 0);
}

unsigned TileManager::GetTileIndex(Tile tile)
{
    switch (tile)
    {
        case TILE_GRASS_LEFT:   return 1;
        case TILE_GRASS_MID:    return 2;
        case TILE_GRASS_RIGHT:  return 3;
        case TILE_SAND_LEFT:    return 45;
        case TILE_SAND_MID:     return 46;
        case TILE_SAND_RIGHT:   return 47;
    }

    return 0;
}

void TileManager::Draw(Map* map)
{
    TileSet& tiles = map->tiles;

    float ratio = al_get_bitmap_width(bg) / al_get_bitmap_height(bg);
    DrawScaledBitmap(bg, 0, 0, al_get_bitmap_width(bg), al_get_bitmap_height(bg), 0, height, ratio*height, height);

    for (size_t c = 0; c < tiles.size(); ++c)
        for (size_t r = 0; r < 24; ++r)
        {
            if (map->edit_mode)
                DrawFilledRect(c * TileSize - map->offset, r * TileSize, c * TileSize + 2 - map->offset, (r * TileSize + 2), MakeCol(255, 255, 255));

            if (unsigned t = GetTileIndex(tiles[c][r]))
                DrawScaledBitmap(this->tiles,
                    1 + (t-1) % 44 * 17, 1 + (t-1) / 44 * 17, 16, 16,
                    c * TileSize - map->offset, (r+1) * TileSize, TileSize, TileSize, 0);
        }
}
