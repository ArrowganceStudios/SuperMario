#ifndef __GameStates__
#define __GameStates__

#include "common.hpp"

namespace Mario
{
    /// Generic game state class
    struct GameState
    {
        /**
         * @param game Owner game.
         */
        GameState(Game* game) : game(game) {}

        /**
         * Finishes the state, calling OnFinish().
         */
        void Finish() { OnFinish(); }

        /**
         * Update handler.
         * If returns true, map update is suppressed.
         * @param dt Time increment.
         */
        virtual bool OnUpdate(float dt)     { return false; }

        /**
         * Draw handler.
         * If returns true, screen drawing is suppressed.
         * @param height Screen height.
         */
        virtual bool OnDraw(size_t height)  { return false; }

        /**
         * Key press handler.
         * If returns true, keyboard handling is suppressed.
         * @param key Key pressed.
         */
        virtual bool OnKeyDown(int key)     { return false; }

        /**
         * Key release handler.
         * If returns true, keyboard handling is suppressed.
         * @param key Key released.
         */
        virtual bool OnKeyUp(int key)       { return false; }

        /**
         * Finish handler. Notifies the game about state end.
         */
        virtual void OnFinish();

        Game* game;         ///< Owner game
    };

    /// Paused game state class
    struct GamePausedState : public GameState
    {
        /// @copydoc GameState::GameState
        GamePausedState(Game* game) : GameState(game) {}

        /// @copydoc GameState::OnKeyDown
        bool OnKeyDown(int key);

        /// @copydoc GameState::OnUpdate
        bool OnUpdate(float dt);
    };

    /// Game over state class
    struct GameOverState : public GameState
    {
        /// @copydoc GameState::GameState
        GameOverState(Game* game) : GameState(game), timer(0) {}

        /// @copydoc GameState::OnUpdate
        bool OnUpdate(float dt);

        float timer;        ///< State duration timer
    };
}

#endif
