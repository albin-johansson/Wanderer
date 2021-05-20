#pragma once

#include <centurion.hpp>  // farea, frect

#include "core/aliases/entity_type.hpp"
#include "core/aliases/ints.hpp"

namespace wanderer::ctx {

/**
 * \struct viewport
 * \brief Represents an area that is visible for the player.
 *
 * \var viewport::bounds
 * The position and size of the viewport.
 *
 * \var viewport::level_size
 * The size of the level that the viewport is associated with.
 *
 * \var viewport::keep_in_bounds
 * Indicates whether or not the viewport is allowed to be positioned in a way
 * so that the area outside of the level is displayed. This is usually
 * disabled for small levels (e.g. houses) and enabled for the world levels.
 *
 * \headerfile viewport.hpp
 */
struct viewport final
{
  cen::frect bounds;
  cen::farea level_size;
  bool keep_in_bounds{};
};

void serialize(auto& archive, viewport& v, uint32 version)
{
  archive(v.bounds, v.level_size, v.keep_in_bounds);
}

}  // namespace wanderer::ctx
