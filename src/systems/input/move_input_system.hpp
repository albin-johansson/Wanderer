#pragma once

#include <centurion.hpp>
#include <entt.hpp>

#include "player.hpp"

namespace wanderer::sys {

/**
 * \brief Handles the player input if the player is moving.
 *
 * \pre `player` must feature a `movable` component.
 * \pre `player` must feature a `binds` component.
 * \pre `player` must feature a `humanoid_move` component.
 *
 * \param registry the current registry.
 * \param dispatcher the event dispatcher that is being used.
 * \param player the player entity.
 * \param keyboard the current keyboard input state.
 */
void handle_move_input(entt::registry& registry,
                       entt::dispatcher& dispatcher,
                       comp::player::entity player,
                       const cen::keyboard& keyboard);

}  // namespace wanderer::sys
