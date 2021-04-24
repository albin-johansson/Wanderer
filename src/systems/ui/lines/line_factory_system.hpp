#pragma once

#include <entt.hpp>  // registry

#include "components/ui/line.hpp"

namespace wanderer::sys {

/// \name Lines
/// \{

/**
 * \brief Creates a line entity.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 * \param start the start position.
 * \param end the end position.
 *
 * \return the created entity.
 */
auto make_line(entt::registry& registry, grid_position start, grid_position end)
    -> comp::line::entity;

/// \} End of lines

}  // namespace wanderer::sys