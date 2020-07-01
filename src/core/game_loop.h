/**
 * @brief Provides the `GameLoop` class.
 * @file game_loop.h
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include "game.h"
#include "wanderer_stdinc.h"

namespace wanderer {

/**
 * @class GameLoop
 * @brief Represents the game loop logic.
 * @details This class is responsible for updating and managing the game loop
 * related logic, such as the delta time, interpolation coefficient, etc.
 *
 * @headerfile game_loop.h
 */
class GameLoop final {
 public:
  /**
   * @brief Creates a `GameLoop` instance.
   */
  GameLoop() noexcept;

  /**
   * @brief Updates the state of the game loop.
   * @param game the game instance that will be updated.
   */
  void update(Game& game);

  /**
   * @brief Returns the current value of the interpolation coefficient.
   * @return an interpolation coefficient (alpha) value, in the range [0, 1].
   */
  [[nodiscard]] auto alpha() const -> Alpha
  {
    Alpha alpha{m_accumulator.get() / m_timeStep.get()};
    if (alpha > Alpha{1.0f}) {
      alpha = Alpha{1.0f};
    }
    return alpha;
  }

 private:
  u64 m_now;
  u64 m_then;
  Delta m_delta{0};
  Delta m_accumulator{0};
  Delta m_deltaBuffer{0};
  const float m_vsyncRate;
  const Delta m_timeStep;
  const float m_counterFreq;

  /**
   * @brief Returns the maximum allowed frame time (delta time) in seconds.
   * @details This is used to avoid the "spiral of death" in the game loop.
   * @since 0.1.0
   */
  [[nodiscard]] constexpr auto max_frame_time() noexcept -> Delta
  {
    return Delta{0.25f};
  }

  void smooth_delta() noexcept;
};

}  // namespace wanderer
