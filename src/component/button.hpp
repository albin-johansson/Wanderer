#pragma once

#include <cen/point.hpp>    // fpoint
#include <cen/texture.hpp>  // texture
#include <memory>           // unique_ptr
#include <string>           // string

#include "action.hpp"
#include "entity_type.hpp"
#include "maybe.hpp"

namespace wanderer::comp {
namespace detail {
struct button_entity_t;
struct button_drawable_entity_t;
}  // namespace detail

struct button final
{
  using entity = entity_type<detail::button_entity_t>;

  std::unique_ptr<action> action;
  std::string text;
  int row;
  int col;
  bool hover{false};
};

struct button_drawable final
{
  using entity = entity_type<detail::button_drawable_entity_t>;

  mutable cen::frect bounds;
  mutable maybe<cen::texture> texture;
  mutable maybe<cen::fpoint> textPos;
};

}  // namespace wanderer::comp
