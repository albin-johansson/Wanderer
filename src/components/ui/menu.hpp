#pragma once

#include <centurion.hpp>
#include <string>  // string
#include <vector>  // vector

#include "entity_type.hpp"
#include "key_bind.hpp"
#include "maybe.hpp"
#include "menu_id.hpp"
#include "null_entity.hpp"

namespace wanderer::comp {
namespace detail {
struct menu_entity_t;
struct menu_drawable_entity_t;
}  // namespace detail

struct menu final
{
  using entity = entity_type<detail::menu_entity_t>;

  menu_id id;
  std::string title;
  bool blocking;
};

struct home_menu final
{
  menu::entity entity{null<menu>()};
};

struct in_game_menu final
{
  menu::entity entity{null<menu>()};
};

struct settings_menu final
{
  menu::entity entity{null<menu>()};
};

struct controls_menu final
{
  menu::entity entity{null<menu>()};
};

struct menu_drawable final
{
  using entity = entity_type<detail::menu_drawable_entity_t>;

  mutable maybe<cen::texture> texture;  ///< Title text texture.
  mutable maybe<cen::ipoint> position;  ///< The position of the title text.
};

}  // namespace wanderer::comp
