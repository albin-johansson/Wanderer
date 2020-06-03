#pragma once

#include <renderer.h>

#include "types.h"

namespace wanderer {

entt::entity make_player(entt::registry& registry,
                         centurion::Renderer& renderer);

}
