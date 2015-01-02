#include "Player.hpp"

using namespace Mario;

void Player::OnKeyDown(int key)
{
    switch (key)
    {
        case ALLEGRO_KEY_LEFT:
            dir_x = -3*int(TileSize);
            state = STATE_RUN;
            break;

        case ALLEGRO_KEY_RIGHT:
            dir_x = 3*int(TileSize);
            state = STATE_RUN;
            break;

        case ALLEGRO_KEY_Z:
            if (!falling)
            {
                dir_y = 10*int(TileSize);
                falling = true;
                state = STATE_JUMP;
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
            dir_x = 0;
            if (state != STATE_JUMP)
                state = STATE_STAND;
            break;
    }
}

size_t Player::OnDraw()
{
    switch (state)
    {
        case STATE_STAND:
            return 68;

        case STATE_RUN:
            return 69 + (frame = (frame + 1) % 2);

        default:
            return 0;
    }
}
