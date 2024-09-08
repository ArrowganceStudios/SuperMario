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

            default:
                break;
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

            default:
                break;
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
        default:                break;
    }

    return 0;
}

void TileManager::Draw(Map* map, ALLEGRO_BITMAP* bg)
{
    if (!bg)
        bg = this->bg;

    TileSet& tiles = map->tiles;

    float ratio = float(GetBitmapWidth(bg)) / GetBitmapHeight(bg);
    DrawScaledBitmap(bg, 0, 0, GetBitmapWidth(bg), GetBitmapHeight(bg), 0, height, ratio*height, height);

    for (size_t c = 0; c < tiles.size(); c++)
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
