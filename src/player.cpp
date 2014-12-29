#include "player.hpp"

using namespace Mario;

void Player::OnKeyDown(int key)
{
    switch (key)
    {
        case ALLEGRO_KEY_LEFT:
            dir_x = -1;
            break;

        case ALLEGRO_KEY_RIGHT:
            dir_x = 1;
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
            break;
    }
}
