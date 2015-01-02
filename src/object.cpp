#include "object.hpp"

using namespace Mario;

void Object::OnUpdate(float dt)
{
    if (falling)
        dir_y += -Gravity * dt;
    else if (dir_y != 0)
        dir_y = 0;

    pos_x += dir_x * dt;
    pos_y += dir_y * dt;
}

void Object::OnDraw(size_t height)
{
    al_draw_filled_rectangle(pos_x-TileSize/2, height-pos_y, pos_x + TileSize/2, height-(pos_y + TileSize), al_map_rgb(255, 255, 255));
}
