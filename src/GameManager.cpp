/**
 * @file        GameManager.cpp
 * @author      mg6 (maciej@gamrat.it)
 * @date        2014-2015
 * @copyright   GNU GPL v2
 */

#include "Game.hpp"
#include "GameStates.hpp"
#include "GameManager.hpp"

using namespace Mario;

void GameManager::Init()
{
    srand(time(nullptr));

    if (!al_init())
        throw std::runtime_error("Could not initialize Allegro.");

    if (!al_install_keyboard())
        throw std::runtime_error("Could not initialize keyboard.");

    if (!al_install_mouse())
        throw std::runtime_error("Could not initialize mouse.");

    if (!al_init_image_addon())
        throw std::runtime_error("Could not initialize Allegro image utilities.");

    al_init_font_addon();

    if (!al_init_ttf_addon())
        throw std::runtime_error("Could not initialize font utilities.");

    if (!(font = al_load_font(ASSETS "overlay.otf", 18, 0)))
        throw std::runtime_error("Could not load overlay font.");

    if (!al_init_primitives_addon())
        throw std::runtime_error("Could not initialize Allegro primitives.");

    al_set_new_display_flags(ALLEGRO_WINDOWED);
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    if (!(display = al_create_display(width, height)))
        throw std::runtime_error("Could not create display.");

    if (!(redraw_timer = al_create_timer(1.0/fps)))
        throw std::runtime_error("Could not create redraw timer.");

    if (!(update_timer = al_create_timer(1.0/ups)))
        throw std::runtime_error("Could not create update timer.");

    if (!(queue = al_create_event_queue()))
        throw std::runtime_error("Could not create event queue.");

    al_set_window_title(display, "Super Mario: OO Adventures");

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(redraw_timer));
    al_register_event_source(queue, al_get_timer_event_source(update_timer));

    al_start_timer(redraw_timer);
    al_start_timer(update_timer);

    sprite_mgr = new SpriteManager(width, height, 0, 0);
    tile_mgr = new TileManager(width, height, 0, 0);
    splash_mgr = new SplashScreenManager(this, sprite_mgr, tile_mgr);
}

void GameManager::Loop()
{
    ALLEGRO_EVENT e;
    bool redraw = false;

    while (!IsDone())
    {
        if (game && game->done)
        {
            delete game;
            game = nullptr;
        }

        al_wait_for_event(queue, &e);

        switch (e.type)
        {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
            {
                done = true;
                break;
            }

            case ALLEGRO_EVENT_KEY_DOWN:
            {
                if (e.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                {
                    done = true;
                    break;
                }
                else if (!game && e.keyboard.keycode == ALLEGRO_KEY_SPACE)
                    game = new Game();

                if (!game)
                    break;

                switch (e.keyboard.keycode)
                {
                    case ALLEGRO_KEY_F1:
                    {
                        game->map->edit_mode = !game->map->edit_mode;
                        log_info("[Game]\tMap edit mode", game->map->edit_mode ? "on" : "off");
                        break;
                    }

                    case ALLEGRO_KEY_F2:
                    {
                        game->SaveMap(ASSETS "map1");
                        break;
                    }

                    case ALLEGRO_KEY_F3:
                    {
                        game->LoadMap(ASSETS "map1");
                        break;
                    }
                }

                if (!game->states.empty() && game->states.back()->OnKeyDown(e.keyboard.keycode))
                    break;

                if (e.keyboard.keycode == ALLEGRO_KEY_P)
                {
                    game->states.push_back(new GamePausedState(game));
                    break;
                }

                if (game->player)
                    game->player->OnKeyDown(e.keyboard.keycode);
                break;
            }

            case ALLEGRO_EVENT_KEY_UP:
            {
                if (game && !game->states.empty() && game->states.back()->OnKeyUp(e.keyboard.keycode))
                    break;

                switch (e.keyboard.keycode)
                {
                    case ALLEGRO_KEY_LEFT:
                    case ALLEGRO_KEY_RIGHT:
                    case ALLEGRO_KEY_UP:
                    case ALLEGRO_KEY_DOWN:
                    case ALLEGRO_KEY_X:
                    case ALLEGRO_KEY_Z:
                        if (game && game->player)
                            game->player->OnKeyUp(e.keyboard.keycode);
                        break;
                }
                break;
            }

            case ALLEGRO_EVENT_MOUSE_AXES:
            {
                if (!game || !game->map->edit_mode || e.mouse.dz == 0)
                    break;

                size_t tile_x = floor((game->map->offset + e.mouse.x)/TileSize);
                size_t tile_y = floor((height-e.mouse.y)/TileSize);
                int t = game->map->tiles[tile_x][tile_y] + e.mouse.dz;
                if (t < 0) t += MAX_TILE_TYPE;
                game->map->tiles[tile_x][tile_y] = Tile(t % MAX_TILE_TYPE);
                break;
            }

            case ALLEGRO_EVENT_TIMER:
            {
                if (e.timer.source == update_timer)
                {
                    static double old_time = 0;
                    double cur_time = GetTime();

                    Update(float(cur_time - old_time));

                    old_time = cur_time;
                }
                else if (e.timer.source == redraw_timer)
                    redraw = true;
                break;
            }
        }

        if (redraw && al_is_event_queue_empty(queue))
        {
            redraw = false;
            Draw();
        }
    }
}

void GameManager::Cleanup()
{
    if (game)
        delete game;

    if (sprite_mgr)
        delete sprite_mgr;

    if (tile_mgr)
        delete tile_mgr;

    if (splash_mgr)
        delete splash_mgr;

    if (redraw_timer)
        al_destroy_timer(redraw_timer);

    if (update_timer)
        al_destroy_timer(update_timer);

    if (font)
        al_destroy_font(font);

    if (display)
        al_destroy_display(display);

    if (queue)
        al_destroy_event_queue(queue);
}

void GameManager::Update(float dt)
{
    if (game)
        game->Update(dt);
    else if (splash_mgr)
        splash_mgr->Update(dt);
}

void GameManager::Draw()
{
    if (game)
    {
        tile_mgr->Draw(game->map);
        sprite_mgr->Draw(game->map);

        PutString(15, 10, 0xffffff, ALLEGRO_ALIGN_LEFT, "Mario x %u", game->num_lives);
        PutString(width-15, 10, 0xffffff, ALLEGRO_ALIGN_RIGHT, "Pts %u", game->points);
    }
    else if (splash_mgr)
        splash_mgr->Draw();

    al_flip_display();
}
