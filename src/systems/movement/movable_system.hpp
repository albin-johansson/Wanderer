#pragma once

#include "direction.hpp"
#include "movable.hpp"

namespace wanderer::sys {

/**
 * \brief Returns the appropriate dominant direction for a movable component.
 *
 * \param movable the movable component that will be used.
 *
 * \return the calculated dominant direction for the movable.
 *
 * \since 0.1.0
 */
[[nodiscard]] auto dominant_direction(const comp::movable& movable) noexcept -> direction;

}  // namespace wanderer::sys
