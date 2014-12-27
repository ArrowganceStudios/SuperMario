#include "map.hpp"
#include "tilemanager.hpp"

using namespace Mario;

ALLEGRO_COLOR TileManager::get_tile_color(Tile& tile)
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
        case TILE_PLAYER_SPAWN:
            return al_map_rgb(255, 0, 0);
        default:
            return al_map_rgb(0, 0, 0);
    }
}

void TileManager::draw_map(size_t height, Map* map)
{
    TileSet& tiles = map->tiles;

    for (int c = 0; c < tiles.size(); ++c)
        for (int r = 0; r < 24; ++r)
            al_draw_filled_rectangle(c * TileSize, height - r * TileSize, (c+1)*TileSize, height - (r+1)*TileSize, get_tile_color(tiles[c][r]));
}
