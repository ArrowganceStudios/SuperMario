/**
 * @file        ScreenHandler.hpp
 * @author      mg6 (maciej@gamrat.it)
 * @date        2014-2015
 * @copyright   GNU GPL v2
 */

#ifndef __ScreenHandler__
#define __ScreenHandler__

#include "Common.hpp"

namespace Mario
{
    template <typename T, typename U>
    class IScreenHandler
    {
    public:
        typedef T P;
        typedef U Color;
        typedef U Size;

    protected:
        Size width;
        Size height;
        P offset_x;
        P offset_y;

    public:
        IScreenHandler() : width(Size()), height(Size()), offset_x(P()), offset_y(P()) {}

        virtual void ClearScreen(Color col) {}
        virtual void DrawBitmap() {}
        virtual void DrawFilledRect(P x1, P y1, P x2, P y2, Color rgb) {}
        virtual void DrawScaledBitmap() {}

        virtual Size GetWidth() { return width; }
        virtual Size GetHeight() { return height; }

        static Color MakeCol(Color r, Color g, Color b)
        {
            return ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF);
        }

        virtual void SetScreenOffset(P offset_x, P offset_y)
        {
            this->offset_x = offset_x;
            this->offset_y = offset_y;
        }

        virtual void SetScreenSize(Size width, Size height)
        {
            this->width = width;
            this->height = height;
        }

        virtual void ToWinCoords(P& x, P& y)
        {
            x += offset_x;
            y = height - y + offset_y;
        }
    };
}

// Desired screen adapter
#include "AllegroHandler.hpp"

#endif
