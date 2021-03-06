#pragma once

#include <centurion.hpp>  // renderer
#include <entt.hpp>       // registry
#include <string>         // string

#include "label.hpp"

namespace wanderer::sys {

auto make_label(entt::registry& registry, std::string text, float x, float y)
    -> comp::label::entity;

void render_labels(const entt::registry& registry,
                   cen::renderer& renderer,
                   const comp::label_pack& pack);

}  // namespace wanderer::sys