#pragma once

#include <entt.hpp>  // registry
#include <string>    // string

#include "components/ui/checkbox.hpp"
#include "core/grid_position.hpp"
#include "core/menu_action.hpp"

namespace wanderer::sys {

/// \name Checkboxes
/// \{

/**
 * \brief Creates a checkbox.
 *
 * \details The created entity will feature `comp::button`, `comp::button_drawable` and
 * `comp::checkbox` components.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 * \param text the text associated with the checkbox.
 * \param position the position of the checkbox.
 * \param action the action that will be associated with the checkbox.
 * \param checked `true` if the checkbox should be checked; `false` otherwise.
 *
 * \return the created entity.
 */
auto make_checkbox(entt::registry& registry,
                   std::string text,
                   grid_position position,
                   menu_action action,
                   const bool checked = false) -> comp::checkbox::entity;

/// \} End of checkboxes

}  // namespace wanderer::sys