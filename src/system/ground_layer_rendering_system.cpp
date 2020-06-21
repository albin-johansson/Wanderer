#include "ground_layer_rendering_system.h"

#include "layer_rendering_system.h"
#include "render_bounds_system.h"
#include "tile_layer.h"
#include "tileset.h"

using centurion::Renderer;

namespace wanderer::system::layer {

void render_ground(entt::registry& registry,
                   const TilemapEntity mapEntity,
                   Renderer& renderer,
                   const RenderBounds& bounds)
{
  const auto& tilemap = registry.get<Tilemap>(mapEntity.get());
  const auto& tileset = registry.get<Tileset>(tilemap.tileset.get());

  for (const auto layer : tilemap.groundLayers) {
    const auto& tileLayer = registry.get<TileLayer>(layer.get());
    layer::render(registry, tileLayer, renderer, tileset, bounds);
  }
}

}  // namespace wanderer::system::layer
