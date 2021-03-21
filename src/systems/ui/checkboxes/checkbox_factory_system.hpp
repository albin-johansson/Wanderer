#pragma once

#include <entt.hpp>  // registry, id_type
#include <string>    // string

#include "checkbox.hpp"
#include "menu_action.hpp"

namespace wanderer::sys {

auto add_checkbox(entt::registry& registry,
                  std::string text,
                  const int row,
                  const int col,
                  entt::id_type id,
                  const bool checked = false) -> comp::checkbox::entity;

}