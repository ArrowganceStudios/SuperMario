/**
 * @file        GameStates.hpp
 * @author      mg6 (maciej@gamrat.it)
 * @date        2014-2015
 * @copyright   GNU GPL v2
 */

#ifndef __GameStates__
#define __GameStates__

#include "Common.hpp"

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
         * @param game_mgr Game manager.
         */
        virtual bool OnDraw(GameManager* game_mgr)
        {
            return false;
        }

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

        /// @copydoc GameState::OnKeyUp
        bool OnKeyUp(int key) { return true; }

        /// @copydoc GameState::OnUpdate
        bool OnUpdate(float dt) { return true; }
    };

    /// Game over state class
    struct GameOverState : public GameState
    {
        /// @copydoc GameState::GameState
        GameOverState(Game* game) : GameState(game), timer(3.0f) { OnInit(); }

        /// Initialize handler.
        void OnInit();

        /// @copydoc GameState::OnKeyDown
        bool OnKeyDown(int key) { return true; }

        /// @copydoc GameState::OnKeyUp
        bool OnKeyUp(int key) { return true; }

        /// @copydoc GameState::OnUpdate
        bool OnUpdate(float dt);

        float timer;        ///< State duration timer
    };

    /// Key help state class
    struct KeyInfoState : public GameState
    {
        /// @copydoc GameState::GameState
        KeyInfoState(Game* game) : GameState(game) {}

        /// @copydoc GameState::OnKeyDown
        bool OnKeyDown(int key);

        /// @copydoc GameState::OnKeyUp
        bool OnKeyUp(int key) { return true; }

        /// @copydoc GameState::OnDraw
        bool OnDraw(GameManager* game_mgr);

        /// @copydoc GameState::OnUpdate
        bool OnUpdate(float dt) { return true; }
    };

    /// Level complete state class
    struct LevelClearState : public GameState
    {
        /// @copydoc GameState::GameState
        LevelClearState(Game* game) : GameState(game), timer(5.0f) {}

        /// @copydoc GameState::OnDraw
        bool OnDraw(GameManager* game_mgr);

        /// @copydoc GameState::OnKeyDown
        bool OnKeyDown(int key) { return true; }

        /// @copydoc GameState::OnKeyUp
        bool OnKeyUp(int key) { return true; }

        /// @copydoc GameState::OnUpdate
        bool OnUpdate(float dt);

        float timer;        ///< State duration timer
    };
}

#endif
