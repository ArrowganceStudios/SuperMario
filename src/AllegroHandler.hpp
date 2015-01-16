/**
 * @file        AllegroHandler.hpp
 * @author      mg6 (maciej@gamrat.it)
 * @date        2014-2015
 * @copyright   GNU GPL v2
 */

#ifndef __AllegroHandler__
#define __AllegroHandler__

namespace Mario
{
    class AllegroHandler : public IScreenHandler<float, int>
    {
    private:
        inline uint8_t r(Color col) { return (col >> 16) & 0xFF; }
        inline uint8_t g(Color col) { return (col >> 8) & 0xFF; }
        inline uint8_t b(Color col) { return col & 0xFF; }

        ALLEGRO_COLOR toColor(Color col)
        {
            return al_map_rgb(r(col), g(col), b(col));
        }

    public:
        void ClearScreen(Color col)
        {
            al_clear_to_color(toColor(col));
        }

        void DrawFilledRect(P x1, P y1, P x2, P y2, Color rgb)
        {
            ToWinCoords(x1, y1);
            ToWinCoords(x2, y2);

            al_draw_filled_rectangle(x1, y1, x2, y2, toColor(rgb));
        }

        void DrawScaledBitmap(ALLEGRO_BITMAP* bmp, P sx, P sy, P sw, P sh,
            P dx, P dy, P dw, P dh, int flags = 0)
        {
            ToWinCoords(dx, dy);

            al_draw_scaled_bitmap(bmp, sx, sy, sw, sh, dx, dy, dw, dh, flags);
        }
    };

    class ScreenHandler : public AllegroHandler {};
};

#endif
