/**
 * @file        Objects.cpp
 * @author      mg6 (maciej@gamrat.it)
 * @date        2014-2015
 * @copyright   GNU GPL v2
 */

#include "Objects.hpp"
#include "Map.hpp"
#include "Game.hpp"

using namespace Mario;

void Object::Kill(Object* enemy)
{
    if (enemy->state & STATE_ALIVE)
    {
        enemy->state &= ~STATE_ALIVE;
        enemy->state |= STATE_FALL;
        enemy->dir_y = 10 * TileSize;
        map->game->OnKill(this, enemy);
    }
}

void Object::OnAnimate(float dt)
{
    anim_timer += dt;

    if (anim_timer > 0.2)
    {
        anim_timer = 0;
        ++frame;
    }
}

void Object::OnMove(float dt)
{
    // apply gravity if falling
    if (!(state & STATE_FLY) && state & STATE_FALL)
        dir_y += -Gravity * dt;

    pos_x += dir_x * dt;
    pos_y += dir_y * dt;
}

void Object::OnUpdate(float dt)
{
    OnMove(dt);
    OnAnimate(dt);
}

void Enemy::OnCollision(Object* spawn)
{
    if (Player* player = dynamic_cast<Player*>(spawn))
    {
        if (pos_y < spawn->pos_y)
            player->Kill(this);
        else
            Kill(player);
    }
}

void Enemy::OnUpdate(float dt)
{
    int tile_x = Map::ToTile(pos_x);
    int tile_y = Map::ToTile(pos_y);
    int tile_n = Map::ToTile(pos_x + dir_x * dt);

    // check if standing on solid tile
    if (Map::IsSolidTile(map->GetTile(tile_x, tile_y - 1)))
        // check if at edge or wall
        if (!Map::IsSolidTile(map->GetTile(tile_n, tile_y - 1)) ||
            Map::IsSolidTile(map->GetTile(tile_n, tile_y)))
            // change direction
            dir_x *= -1;

    Object::OnUpdate(dt);
}

size_t Goomba::OnDraw()
{
    if (!(state & STATE_ALIVE))
        return 2;

    return frame % 2;
}

size_t Koopa::OnDraw()
{
    if (!(state & STATE_ALIVE))
        return 4;

    return (dir_x < 0 ? 0 : 2) + frame % 2;
}

size_t Lakitu::OnDraw()
{
    return 1;
}

void Spiny::OnCollision(Object* spawn)
{
    if (Player* player = dynamic_cast<Player*>(spawn))
        Kill(player);
}

size_t Spiny::OnDraw()
{
    if (!(state & STATE_ALIVE))
        return 4;

    return (dir_x < 0 ? 0 : 2) + frame % 2;
}
