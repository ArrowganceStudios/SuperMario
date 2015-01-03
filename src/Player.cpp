/**
 * @file        Player.cpp
 * @author      mg6 (maciej@gamrat.it)
 * @date        2014-2015
 * @copyright   GNU GPL v2
 */

#include "Player.hpp"

using namespace Mario;

void Player::OnKeyDown(int key)
{
    switch (key)
    {
        case ALLEGRO_KEY_LEFT:
            dir_x = -5*int(TileSize);
            state |= STATE_LEFT;
            state |= STATE_RUN;
            break;

        case ALLEGRO_KEY_RIGHT:
            dir_x = 5*int(TileSize);
            state &= ~STATE_LEFT;
            state |= STATE_RUN;
            break;

        case ALLEGRO_KEY_Z:
            if (!(state & STATE_FALL))
            {
                dir_y = 15*int(TileSize);
                state |= STATE_FALL;
                state |= STATE_JUMP;
            }
            break;
    }
}

void Player::OnKeyUp(int key)
{
    switch (key)
    {
        case ALLEGRO_KEY_LEFT:
        case ALLEGRO_KEY_RIGHT:
            if (state & (STATE_JUMP | STATE_FALL))
                break;

            dir_x = 0;
            state &= ~STATE_RUN;
            break;
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
