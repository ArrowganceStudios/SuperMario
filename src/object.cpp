#include "object.hpp"
#include "map.hpp"
#include "game.hpp"

using namespace Mario;

void Object::Kill(Object* enemy)
{
    if (enemy->state != STATE_DEAD)
    {
        enemy->state = STATE_DEAD;
        map->game->OnKill(this, enemy);
    }
}

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

void Enemy::OnCollision(Object* spawn)
{
    if (Player* player = dynamic_cast<Player*>(spawn))
        Kill(player);
}

void Enemy::OnUpdate(float dt)
{
    Tile at = map->GetTile(Map::ToTile(pos_x), Map::ToTile(pos_y)-1);
    Tile next = map->GetTile(Map::ToTile(pos_x + dir_x * dt), Map::ToTile(pos_y)-1);

    if (Map::IsSolidTile(at) && !Map::IsSolidTile(next))
        dir_x *= -1;

    Object::OnUpdate(dt);
}
