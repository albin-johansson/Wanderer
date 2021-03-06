#pragma once

#include <centurion.hpp>

#include "fullscreen_toggled_event.hpp"
#include "game.hpp"
#include "graphics_context.hpp"
#include "input.hpp"
#include "integer_scaling_toggled_event.hpp"
#include "semi_fixed_game_loop.hpp"

namespace wanderer {

/**
 * \class wanderer_engine
 *
 * \brief Represents the Wanderer application.
 *
 * \details This is the top-level representation of the entire game that
 * handles the application window, input, game state/logic, etc.
 *
 * \since 0.1.0
 *
 * \headerfile wanderer_engine.hpp
 */
class wanderer_engine final : public semi_fixed_game_loop<wanderer_engine>
{
 public:
  /**
   * \brief Initializes the application.
   *
   * \details The application window will always be in windowed mode in debug
   * mode, in order to be able to debug the program with breakpoints.
   *
   * \since 0.1.0
   */
  wanderer_engine();

  /**
   * \brief Runs the game.
   *
   * \return `0` on normal exit.
   */
  auto run() -> int;

  auto update_input() -> bool;

  void update_logic(delta_t dt);

 private:
  cen::window m_window;         ///< Application window.
  graphics_context m_graphics;  ///< Graphics context used for all rendering.
  game m_game;                  ///< Provides game logic and game state.
  input m_input;

  void on_fullscreen_toggled(const event::fullscreen_toggled& event);

  void on_integer_scaling_toggled(const event::integer_scaling_toggled& event);
};

}  // namespace wanderer
