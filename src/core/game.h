/**
 * @brief Provides the `Game` class.
 * @file game.h
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include <renderer.h>

#include "image_cache.h"
#include "input.h"
#include "tilemap.h"
#include "viewport.h"
#include "wanderer_stdinc.h"

namespace wanderer {

/**
 * @class Game
 * @brief Represents the Wanderer game.
 * @details This class is responsible for managing the game state and
 * updating the systems. This class is the core of the entire game.
 *
 * @headerfile game.h
 */
class Game final {
 public:
  /**
   * @brief Creates a `Game` instance.
   * @param renderer the renderer used to create the initial textures.
   */
  explicit Game(ctn::Renderer& renderer);

  ~Game() noexcept;

  /**
   * @brief Responds to user input.
   * @param input the current state of the key and mouse input.
   */
  void handle_input(const Input& input);

  /**
   * @brief Updates the state of the game.
   * @param delta the delta time, in seconds.
   */
  void tick(Delta delta);

  /**
   * @brief Renders the game.
   * @param renderer the renderer used to render the game.
   * @param alpha the interpolation coefficient, in the range [0, 1].
   */
  void render(ctn::Renderer& renderer, Alpha alpha);

 private:
  entt::registry m_registry;  // TODO consider multiple registries
  entt::dispatcher m_dispatcher;

  ImageCache m_imageCache;

  entt::entity m_player;
  comp::Tilemap::entity m_world = null_entity<comp::Tilemap>();
  comp::Viewport::entity m_viewport = null_entity<comp::Viewport>();
};

}  // namespace wanderer
