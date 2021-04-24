#pragma once

#include <centurion.hpp>  // texture, fpoint
#include <string>         // string

#include "core/aliases/entity_type.hpp"
#include "core/aliases/maybe.hpp"
#include "core/grid_position.hpp"
#include "core/menu_action.hpp"

namespace wanderer::comp {
namespace detail {
struct button_entity_t;
struct button_drawable_entity_t;
}  // namespace detail

struct button final
{
  using entity = entity_type<detail::button_entity_t>;

  menu_action action;
  std::string text;
  grid_position position;
  bool enabled{true};
  bool hover{false};
  bool visible{true};
};

struct button_drawable final
{
  using entity = entity_type<detail::button_drawable_entity_t>;

  mutable cen::frect bounds;
  mutable maybe<cen::texture> texture;
  mutable maybe<cen::fpoint> textPos;
};

}  // namespace wanderer::comp
