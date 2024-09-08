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
    if (IsFalling())
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
    if (!IsAlive())
        return;

    switch (key)
    {
        case ALLEGRO_KEY_DOWN:
            keys_down |= KEY_STATE_DOWN;
            break;

        case ALLEGRO_KEY_LEFT:
            keys_down |= KEY_STATE_LEFT;
            dir_x = -5.0f * TileSize;
            SetState(STATE_LEFT);
            SetState(STATE_RUN);
            break;

        case ALLEGRO_KEY_RIGHT:
            keys_down |= KEY_STATE_RIGHT;
            dir_x = 5.0f * TileSize;
            ClearState(STATE_LEFT);
            SetState(STATE_RUN);
            break;

        case ALLEGRO_KEY_X:
        case ALLEGRO_KEY_UP:
            keys_down |= KEY_STATE_UP;
            if (!IsFalling())
            {
                dir_y = 15*int(TileSize);
                SetState(STATE_FALL);
                SetState(STATE_JUMP);
            }
            break;

        case ALLEGRO_KEY_Z:
            keys_down |= KEY_STATE_RUN;
            if (!IsFalling())
                dir_x_boost = RUN_BOOST;
            break;
    }
}

void Player::OnKeyUp(int key)
{
    // clear key state flags
    switch (key)
    {
        case ALLEGRO_KEY_Z:
            keys_down &= ~KEY_STATE_RUN;
            if (!IsFalling())
                dir_x_boost = 1.0f;
            break;

        case ALLEGRO_KEY_X:
        case ALLEGRO_KEY_UP:    keys_down &= ~KEY_STATE_UP;     break;
        case ALLEGRO_KEY_DOWN:  keys_down &= ~KEY_STATE_DOWN;   break;
        case ALLEGRO_KEY_LEFT:  keys_down &= ~KEY_STATE_LEFT;   break;
        case ALLEGRO_KEY_RIGHT: keys_down &= ~KEY_STATE_RIGHT;  break;
    }

    // if both left and right keys are released
    if (!(keys_down & (KEY_STATE_LEFT | KEY_STATE_RIGHT)))
    {
        // stop running
        if (IsRunning())
            ClearState(STATE_RUN);

        // reset speed if running or decrease if mid-air
        if (dir_x != 0)
            dir_x = (HasState(STATE_JUMP) || IsFalling()) ?
                (HasState(STATE_LEFT) ? -1.0f : 1.0f) * TileSize : 0;
    }
}

size_t Player::OnDraw()
{
    if (!IsAlive())
        return 52;

    if (HasState(STATE_JUMP))
        return HasState(STATE_LEFT) ? 106 : 118;

    if (HasState(STATE_FALL))
        return HasState(STATE_LEFT) ? 61 : 73;

    if (HasState(STATE_RUN))
        return (HasState(STATE_LEFT) ? 64 : 68) + frame % 3;

    if (HasState(STATE_VICTORY))
        return 115;

    return HasState(STATE_LEFT) ? 66 : 68;
}
