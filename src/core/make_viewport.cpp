#include "make_viewport.h"

#include "game_constants.h"
#include "viewport.h"

namespace wanderer {

entt::entity make_viewport(entt::registry& registry)
{
  const auto entity = registry.create();

  auto& viewport = registry.emplace<Viewport>(entity);
  viewport.set_bounds({{0, 0},
                       {static_cast<float>(g_logicalWidth),
                        static_cast<float>(g_logicalHeight)}});
  viewport.set_level_size({1000, 1000});  // FIXME update automatically
  return entity;
}

}  // namespace wanderer
