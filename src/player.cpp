#include "player.hpp"

using namespace Mario;

void Player::OnKeyDown(int key)
{
    switch (key)
    {
        case ALLEGRO_KEY_LEFT:
            dir_x = -3*int(TileSize);
            break;

        case ALLEGRO_KEY_RIGHT:
            dir_x = 3*int(TileSize);
            break;

        case ALLEGRO_KEY_Z:
            if (!falling)
            {
                dir_y = 10*int(TileSize);
                falling = true;
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
            break;
    }
}
