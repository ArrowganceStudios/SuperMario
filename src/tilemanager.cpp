#include "map.hpp"
#include "tilemanager.hpp"

using namespace Mario;

ALLEGRO_COLOR TileManager::GetTileColor(Map* map, Tile& tile)
{
    switch (tile)
    {
        case TILE_EMPTY:
            return al_map_rgb(0, 127, 255);

        case TILE_GRASS:
            return al_map_rgb(0, 255, 0);

        case TILE_SAND:
            return al_map_rgb(255, 255, 127);

        case TILE_WALL:
            return al_map_rgb(255, 127, 0);
    }

    if (map->edit_mode)
        switch (tile)
        {
            case TILE_PLAYER_SPAWN:
                return al_map_rgb(255, 0, 0);

            case TILE_GOOMBA_SPAWN:
                return al_map_rgb(255, 0, 0);

            case TILE_KOOPA_SPAWN:
                return al_map_rgb(255, 255, 0);

            case TILE_LAKITU_SPAWN:
                return al_map_rgb(127, 0, 255);

            case TILE_SPINY_SPAWN:
                return al_map_rgb(255, 0, 127);
        }

    return al_map_rgb(0, 127, 255);
}

void TileManager::DrawMap(Map* map, size_t height)
{
    TileSet& tiles = map->tiles;

    for (int c = 0; c < tiles.size(); ++c)
        for (int r = 0; r < 24; ++r)
            al_draw_filled_rectangle(c * TileSize, height - r * TileSize, (c+1)*TileSize, height - (r+1)*TileSize, GetTileColor(map, tiles[c][r]));
}
