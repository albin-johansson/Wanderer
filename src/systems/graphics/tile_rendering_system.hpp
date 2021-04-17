#pragma once

#include "components/ctx/tileset.hpp"
#include "components/map/tile.hpp"
#include "core/graphics/graphics_context.hpp"

namespace wanderer::sys {

/// \name Tiles
/// \{

// TODO make row and col floats
void render_tile(graphics_context& graphics,
                 const comp::tile& tile,
                 int row,
                 int col) noexcept;

[[nodiscard]] auto get_animated_tile(const entt::registry& registry,
                                     comp::tile::entity tileEntity,
                                     const ctx::tileset& tileset) -> const comp::tile&;

/// \} End of tiles

}  // namespace wanderer::sys
