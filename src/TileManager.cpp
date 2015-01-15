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
    switch (tile)
    {
        case TILE_EMPTY:
            return RGB(0, 127, 255);

        case TILE_GRASS:
            return RGB(0, 255, 0);

        case TILE_SAND:
            return RGB(255, 255, 127);

        case TILE_WALL:
            return RGB(255, 127, 0);
    }

    if (map->edit_mode)
        switch (tile)
        {
            case TILE_PLAYER_SPAWN:
                return RGB(255, 0, 0);

            case TILE_GOOMBA_SPAWN:
                return RGB(255, 0, 0);

            case TILE_KOOPA_SPAWN:
                return RGB(255, 255, 0);

            case TILE_LAKITU_SPAWN:
                return RGB(127, 0, 255);

            case TILE_SPINY_SPAWN:
                return RGB(255, 0, 127);
        }
    else
        switch (tile)
        {
            case TILE_PLAYER_SPAWN:
            case TILE_GOOMBA_SPAWN:
            case TILE_KOOPA_SPAWN:
            case TILE_LAKITU_SPAWN:
            case TILE_SPINY_SPAWN:
                return RGB(0, 127, 255);
        }

    return RGB(0, 0, 0);
}

unsigned TileManager::GetTileIndex(Tile tile)
{
    switch (tile)
    {
        case TILE_GRASS:    return 1;
        case TILE_WALL:     return 45;

        default:            return unsigned(tile);
    }
}

void TileManager::Draw(Map* map)
{
    TileSet& tiles = map->tiles;

    for (int c = 0; c < tiles.size(); ++c)
        for (int r = 0; r < 24; ++r)
        {
            DrawFilledRect(c * TileSize - map->offset, r * TileSize, (c+1)*TileSize - map->offset, (r+1)*TileSize, GetTileColor(map, tiles[c][r]));

            if (map->edit_mode)
                DrawFilledRect(c * TileSize - map->offset, r * TileSize, c * TileSize + 2 - map->offset, (r * TileSize + 2), RGB(255, 255, 255));

            if (unsigned t = GetTileIndex(tiles[c][r]))
                DrawScaledBitmap(this->tiles,
                    1 + t % 44 * 17, 1 + t / 44 * 17, 16, 16,
                    c * TileSize, (r+1) * TileSize, TileSize, TileSize, 0);
        }
}
