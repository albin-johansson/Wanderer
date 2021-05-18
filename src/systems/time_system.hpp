#pragma once

#include <entt.hpp>  // registry
#include <rune.hpp>  // delta_time

#include "core/graphics/graphics_context.hpp"

namespace wanderer::sys {

/// \name Time
/// \{

/**
 * \brief Updates the state of the time.
 *
 * \ingroup systems
 *
 * \param shared the shared data registry, since levels share their time data.
 * \param dispatcher the event dispatcher that will be used.
 * \param dt the current delta time.
 *
 * \see `ctx::time_of_day`
 */
void update_time(entt::registry& shared,
                 entt::dispatcher& dispatcher,
                 rune::delta_time dt);

/**
 * \brief Renders a digital clock in the upper left corner of the screen with the current
 * time.
 *
 * \ingroup systems
 *
 * \param registry the shared data registry, since levels share their time data.
 * \param graphics the graphics context that will be used.
 */
void render_clock(const entt::registry& registry, graphics_context& graphics);

/// \} End of time

}  // namespace wanderer::sys
