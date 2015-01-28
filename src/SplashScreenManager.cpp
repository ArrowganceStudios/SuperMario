/**
 * @file        SplashScreenManager.cpp
 * @author      mg6 (maciej@gamrat.it)
 * @date        2014-2015
 * @copyright   GNU GPL v2
 */

#include "SplashScreenManager.hpp"

using namespace Mario;

void SplashPlayer::OnUpdate(float dt)
{
    switch (rand() % 100)
    {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            if (!(state & STATE_FALL))
            {
                state |= STATE_JUMP | STATE_FALL;
                dir_y = float(rand() % 10 + 5.0f) * TileSize;
            }
            break;

        case 10:
            if (state & STATE_ALIVE)
            {
                state |= STATE_LEFT | STATE_RUN;
                dir_x = -5.0f * TileSize;
            }
            break;

        case 20:
            if (state & STATE_ALIVE)
            {
                state &= ~STATE_LEFT | STATE_RUN;
                dir_x = 5.0f * TileSize;
            }
            break;

        case 30:
            if (state & STATE_RUN)
            {
                state &= ~STATE_RUN;
                dir_x = 0;
            }
            break;
    }

    Player::OnUpdate(dt);
};

SplashScreenManager::SplashScreenManager(GameManager* owner, SpriteManager*
    sprite_mgr, TileManager* tile_mgr) : owner(owner), sprite_mgr(sprite_mgr),
    tile_mgr(tile_mgr), splash(nullptr), logo(nullptr), player(nullptr)
{
    if (!(splash = al_load_bitmap(ASSETS "splash.png")))
        throw std::runtime_error("[Splash] Could not load splash screen.");

    if (!(logo = al_load_bitmap(ASSETS "logo.png")))
        throw std::runtime_error("[Splash] Could not load game logo.");

    map = new Map(this, ASSETS "splash1");
    map->AddPlayer(new SplashPlayer(map, 14, 4));
    player = map->GetPlayer();
}

SplashScreenManager::~SplashScreenManager()
{
    if (splash)
        al_destroy_bitmap(splash);

    if (logo)
        al_destroy_bitmap(logo);

    delete map;
}

void SplashScreenManager::Draw()
{
    tile_mgr->Draw(map, splash);
    sprite_mgr->Draw(map);

    owner->PutString(owner->width/2-1, owner->height-4*TileSize/3-1, 0xffffff, ALLEGRO_ALIGN_CENTER, "Press SPACE to start");
    tile_mgr->DrawBitmap(logo, float(owner->width-ScreenHandler::GetBitmapWidth(logo))/2, 50, 0);
}

void SplashScreenManager::Update(float dt)
{
    map->Update(dt);

    switch (rand() % 1000)
    {
        case 0:
            map->AddObject(new Goomba(map, rand() % 20, 2));
            break;

        case 1:
            map->AddObject(new Koopa(map, rand() % 20, 2));
            break;

        case 2:
            map->AddObject(new Spiny(map, rand() % 20, 2));
            break;

        case 3:
            Koopa* koopa = new Koopa(map, rand() % 20, 2);
            koopa->shell = true;
            koopa->dir_x *= 10;
            map->AddObject(koopa);
            break;
    }
}

void SplashScreenManager::OnObjectOutOfMap(Object* object)
{
    if (dynamic_cast<Player*>(object))
    {
        Player* player = new SplashPlayer(map, rand() % 20, 16);
        player->dir_x = float(rand() % 10) - 5.0f;
        map->AddPlayer(player);
    }
}
