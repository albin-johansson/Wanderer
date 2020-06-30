#pragma once

#include "viewport.h"
#include "wanderer_stdinc.h"

namespace wanderer {

[[nodiscard]] auto make_viewport(entt::registry& registry) -> Viewport::entity;

}  // namespace wanderer
