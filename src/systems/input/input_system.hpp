#pragma once

#include <entt.hpp>  // registry, dispatcher

#include "components/ctx/binds.hpp"
#include "components/ctx/player.hpp"
#include "core/input.hpp"

namespace wanderer::sys {

/// \name Input
/// \{

/**
 * \brief Handles the current player input.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 * \param dispatcher the event dispatcher that will be used.
 * \param input the current input state.
 * \param binds the current input binds.
 */
void update_input(entt::registry& registry,
                  entt::dispatcher& dispatcher,
                  const input& input,
                  const ctx::binds& binds);

/// \} End of input

}  // namespace wanderer::sys
