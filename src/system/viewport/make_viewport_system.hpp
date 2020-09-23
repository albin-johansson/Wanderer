#pragma once

#include "viewport.hpp"
#include "wanderer_stdinc.hpp"

namespace wanderer::sys::viewport {

[[nodiscard]] auto make_viewport(entt::registry& registry)
    -> comp::Viewport::entity;

}  // namespace wanderer::sys::viewport
