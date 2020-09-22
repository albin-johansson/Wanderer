#pragma once

#include <renderer.hpp>

#include "tile.h"
#include "tileset.h"

namespace wanderer::sys::tile {

void render(cen::renderer& renderer,
            const comp::Tile& tile,
            int row,
            int col) noexcept;

[[nodiscard]] auto animated_tile(entt::registry& registry,
                                 const comp::Tile::entity tileEntity,
                                 const comp::Tileset& tileset)
    -> const comp::Tile&;

}  // namespace wanderer::sys::tile
