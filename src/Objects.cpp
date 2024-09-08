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
        enemy->OnKill(this);

        if (map && map->game)
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

void Object::OnKill(Object* killer)
{
    state |= STATE_FALL;
    dir_y = 10 * TileSize;
    dir_x_boost = 1.0f;
    dir_x = killer->dir_x * killer->dir_x_boost;
}

void Object::OnMove(float dt)
{
    // apply gravity if falling
    if (!(state & STATE_FLY) && state & STATE_FALL)
        dir_y += -Gravity * dt;

    pos_x += dir_x * dt * dir_x_boost;
    pos_y += dir_y * dt;
}

void Object::OnUpdate(float dt)
{
    OnMove(dt);
    OnAnimate(dt);
}

void Enemy::OnCollision(Object* enemy)
{
    if (Player* player = dynamic_cast<Player*>(enemy))
    {
        if (pos_y < enemy->pos_y)
            player->Kill(this);
        else
            Kill(enemy);
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

void Goomba::OnKill(Object* killer)
{
    if (Koopa* koopa = dynamic_cast<Koopa*>(killer))
        Object::OnKill(killer);
    else
        dir_x = 0;
}

void Goomba::OnUpdate(float dt)
{
    Enemy::OnUpdate(dt);

    if (!(state & STATE_ALIVE))
    {
        if (timer <= dt)
        {
            dir_y = -1000.0f * TileSize;
            timer = 1000;
        }
        else
            timer -= dt;
    }
}

void Koopa::OnCollision(Object* enemy)
{
    if (shell && dir_x != 0)
    {
        Kill(enemy);
        return;
    }

    Player* player = dynamic_cast<Player*>(enemy);

    if (!player)
        return;

    if (shell)
    {
        dir_x = (pos_x > enemy->pos_x ? 1.0 : -1.0) * 10 * TileSize;
        return;
    }
    else if (pos_y < enemy->pos_y)
    {
        shell = true;
        dir_x = 0;
        return;
    }

    Kill(enemy);
}

size_t Koopa::OnDraw()
{
    if (!(state & STATE_ALIVE))
        return 4;

    if (shell)
        return 4 + (dir_x != 0 ? frame % 4 : 0);

    return (dir_x < 0 ? 0 : 2) + frame % 2;
}

void Koopa::OnUpdate(float dt)
{
    if (shell)
        Object::OnUpdate(dt);
    else
        Enemy::OnUpdate(dt);
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
