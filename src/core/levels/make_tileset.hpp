#pragma once

#include <entt.hpp>  // registry

#include "components/ctx/tileset.hpp"
#include "core/graphics/graphics_context.hpp"
#include "io/map/parse_ir.hpp"

namespace wanderer {

void load_tileset_textures(const ir::level& data, graphics_context& graphics);

[[nodiscard]] auto make_tileset(const std::vector<ir::tileset>& data,
                                entt::registry& registry,
                                const graphics_context& graphics) -> ctx::tileset&;

}  // namespace wanderer