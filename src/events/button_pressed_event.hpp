#pragma once

#include <entt.hpp>  // id_type

#include "core/menu_action.hpp"

namespace wanderer {

struct button_pressed_event final
{
  menu_action action;
  entt::id_type source;
};

}  // namespace wanderer