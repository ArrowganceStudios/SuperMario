#include "game.hpp"
#include "gamemanager.hpp"

using namespace Mario;

void GameManager::init()
{
    if (!al_init())
        exit(1);

    if (!al_install_keyboard())
        exit(1);

    if (!al_install_mouse())
        exit(1);

    al_set_new_display_flags(ALLEGRO_WINDOWED);
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    if (!(redraw_timer = al_create_timer(1.0/fps)))
        exit(1);

    if (!(update_timer = al_create_timer(1.0/ups)))
        exit(1);

    if (!(display = al_create_display(width, height)))
        exit(1);

    if (!(queue = al_create_event_queue()))
        exit(1);

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(redraw_timer));
    al_register_event_source(queue, al_get_timer_event_source(update_timer));

    al_start_timer(redraw_timer);
    al_start_timer(update_timer);

    tile_mgr = new TileManager();
    game = new Game();
}

void GameManager::loop()
{
    ALLEGRO_EVENT e;
    bool redraw = false;

    while (!isDone())
    {
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
                switch (e.keyboard.keycode)
                {
                    case ALLEGRO_KEY_ESCAPE:
                    {
                        done = true;
                        break;
                    }

                    case ALLEGRO_KEY_F2:
                    {
                        game->save_map("level1.txt");
                        break;
                    }

                    case ALLEGRO_KEY_F3:
                    {
                        game->load_map("level1.txt");
                        break;
                    }
                }
                break;
            }

            case ALLEGRO_EVENT_MOUSE_AXES:
            {
                if (e.mouse.dz == 0)
                    break;

                size_t tile_x = floor(e.mouse.x/TileSize + 0.5);
                size_t tile_y = floor((height-e.mouse.y)/TileSize + 0.5);
                int t = game->map->tiles[tile_x][tile_y] + e.mouse.dz;
                if (t < 0) t += MAX_TILE;
                game->map->tiles[tile_x][tile_y] = Tile(t % MAX_TILE);
                break;
            }

            case ALLEGRO_EVENT_TIMER:
            {
                if (e.timer.source == update_timer)
                {
                    static float old_time = 0;
                    float cur_time = al_get_time();
                    if (!isPaused()) update(cur_time - old_time);
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
            draw();
        }
    }
}

void GameManager::cleanup()
{
    if (game)
        delete game;

    if (tile_mgr)
        delete tile_mgr;

    if (redraw_timer)
        al_destroy_timer(redraw_timer);

    if (update_timer)
        al_destroy_timer(update_timer);

    if (display)
        al_destroy_display(display);

    if (queue)
        al_destroy_event_queue(queue);
}

void GameManager::update(float dt)
{}

void GameManager::draw()
{
    al_clear_to_color(al_map_rgb(255, 255, 255));
    tile_mgr->draw_map(height, game->map);
    al_flip_display();
}
