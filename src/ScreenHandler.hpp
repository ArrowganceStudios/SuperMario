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
    /**
     * Screen handler interface class.
     * @param T Coordinate type.
     * @param U Color/size type.
     */
    template <typename T, typename U>
    class IScreenHandler
    {
    public:
        typedef T P;        ///< Coordinate type
        typedef U Color;    ///< Color type
        typedef U Size;     ///< Width/height type

    protected:
        Size width;         ///< Screen width
        Size height;        ///< Screen height
        P offset_x;         ///< Screen X offset
        P offset_y;         ///< Screen Y offset

    public:
        IScreenHandler() : width(Size()), height(Size()), offset_x(P()), offset_y(P()) {}

        /**
         * Clears the screen to given color.
         * @param col Color.
         */
        virtual void ClearScreen(Color col) {}

        /// Draws bitmap on screen.
        virtual void DrawBitmap() {}

        /**
         * Draws filled rectangle.
         * @param x1 x1
         * @param y1 y1
         * @param x2 x2
         * @param y2 y2
         * @param col Color
         */
        virtual void DrawFilledRect(P x1, P y1, P x2, P y2, Color col) {}

        /// Draws scaled bitmap on screen.
        virtual void DrawScaledBitmap() {}

        /// Returns screen width.
        virtual Size GetWidth() { return width; }

        /// Returns screen height.
        virtual Size GetHeight() { return height; }

        /**
         * Returns color value from RGB values.
         * @param r Red.
         * @param g Green.
         * @param b Blue.
         */
        static Color MakeCol(Color r, Color g, Color b)
        {
            return ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF);
        }

        /**
         * Sets screen offset.
         * @param offset_x OX offset.
         * @param offset_y OY offset.
         */
        virtual void SetScreenOffset(P offset_x, P offset_y)
        {
            this->offset_x = offset_x;
            this->offset_y = offset_y;
        }

        /**
         * Sets screen size.
         * @param width Width.
         * @param height Height.
         */
        virtual void SetScreenSize(Size width, Size height)
        {
            this->width = width;
            this->height = height;
        }

        /**
         * Converts coords to window coords, taking offset into account.
         * @param x X coord.
         * @param y Y coord.
         */
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
