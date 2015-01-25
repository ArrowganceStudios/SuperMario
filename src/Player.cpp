/**
 * @file        Player.cpp
 * @author      mg6 (maciej@gamrat.it)
 * @date        2014-2015
 * @copyright   GNU GPL v2
 */

#include "Player.hpp"

using namespace Mario;

void Player::Kill(Object* enemy)
{
    if (state & STATE_FALL)
        dir_y = (keys_down & KEY_STATE_UP ? 15.0 : 2.0) * int(TileSize);

    Object::Kill(enemy);
}

void Player::OnAnimate(float dt)
{
    anim_timer += dt;

    if (anim_timer > 0.1)
    {
        anim_timer = 0;
        ++frame;
    }
}

void Player::OnKeyDown(int key)
{
    switch (key)
    {
        case ALLEGRO_KEY_DOWN:
            keys_down |= KEY_STATE_DOWN;
            break;

        case ALLEGRO_KEY_LEFT:
            keys_down |= KEY_STATE_LEFT;
            dir_x = -5.0f * TileSize;
            state |= STATE_LEFT;
            state |= STATE_RUN;
            break;

        case ALLEGRO_KEY_RIGHT:
            keys_down |= KEY_STATE_RIGHT;
            dir_x = 5.0f * TileSize;
            state &= ~STATE_LEFT;
            state |= STATE_RUN;
            break;

        case ALLEGRO_KEY_Z:
        case ALLEGRO_KEY_UP:
            keys_down |= KEY_STATE_UP;
            if (!(state & STATE_FALL))
            {
                dir_y = 15*int(TileSize);
                state |= STATE_FALL;
                state |= STATE_JUMP;
            }
            break;

        case ALLEGRO_KEY_X:
            keys_down |= KEY_STATE_X;
            if (!(state & STATE_FALL))
                dir_x_boost = RUN_BOOST;
            break;
    }
}

void Player::OnKeyUp(int key)
{
    // clear key state flags
    switch (key)
    {
        case ALLEGRO_KEY_X:
            keys_down &= ~KEY_STATE_X;
            if (!(state & STATE_FALL))
                dir_x_boost = 1.0f;
            break;

        case ALLEGRO_KEY_Z:
        case ALLEGRO_KEY_UP:    keys_down &= ~KEY_STATE_UP;     break;
        case ALLEGRO_KEY_DOWN:  keys_down &= ~KEY_STATE_DOWN;   break;
        case ALLEGRO_KEY_LEFT:  keys_down &= ~KEY_STATE_LEFT;   break;
        case ALLEGRO_KEY_RIGHT: keys_down &= ~KEY_STATE_RIGHT;  break;
    }

    // if both left and right keys are released
    if (!(keys_down & (KEY_STATE_LEFT | KEY_STATE_RIGHT)))
    {
        // stop running
        if (state & STATE_RUN)
            state &= ~STATE_RUN;

        // stop if not jumping or falling
        if (!(state & (STATE_JUMP | STATE_FALL)))
            dir_x = 0;
    }
}

size_t Player::OnDraw()
{
    if (!(state & STATE_ALIVE))
        return 52;

    if (state & STATE_JUMP)
        return state & STATE_LEFT ? 106 : 118;

    if (state & STATE_FALL)
        return state & STATE_LEFT ? 61 : 73;

    if (state & STATE_RUN)
        return (state & STATE_LEFT ? 64 : 68) + frame % 3;

    return state & STATE_LEFT ? 66 : 68;
}
