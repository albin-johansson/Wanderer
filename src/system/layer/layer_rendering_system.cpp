#include "layer_rendering_system.h"

#include "animated_tile.h"
#include "tile_rendering_system.h"

using centurion::Renderer;

namespace wanderer::system::layer {

void render(entt::registry& registry,
            const TileLayer& layer,
            Renderer& renderer,
            const Tileset& tileset,
            const RenderBounds& bounds)
{
  for (auto row = bounds.minRow; row < bounds.maxRow; ++row) {
    for (auto col = bounds.minCol; col < bounds.maxCol; ++col) {
      const auto r = static_cast<std::size_t>(row);
      const auto c = static_cast<std::size_t>(col);

      const auto tileID = layer.matrix.at(r).at(c);
      if (tileID == g_emptyTile) {
        continue;
      }

      const auto tileEntity = tileset.tiles.at(tileID);

      if (registry.has<AnimatedTile>(tileEntity)) {
        const auto& tile = tile::animated_tile(registry, tileEntity, tileset);
        tile::render(renderer, tile, row, col);
      } else {
        const auto& tile = registry.get<Tile>(tileEntity);
        tile::render(renderer, tile, row, col);
      }
    }
  }
}

}  // namespace wanderer::system::layer
