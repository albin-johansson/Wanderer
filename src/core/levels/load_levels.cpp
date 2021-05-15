#include "load_levels.hpp"

#include "components/ctx/viewport.hpp"
#include "components/map/level.hpp"
#include "components/outside_level.hpp"
#include "core/resources.hpp"
#include "io/map/parse_world.hpp"
#include "systems/levels/level_factory_system.hpp"

namespace wanderer {
namespace {

[[nodiscard]] auto create_world(entt::registry& shared,
                                graphics_context& graphics,
                                const ir::world& data) -> entt::entity
{
  const auto entity = shared.create();

  auto& world = shared.emplace<comp::level>(entity, sys::make_level(data.base, graphics));
  world.registry.ctx<ctx::viewport>().keepInBounds = true;

  shared.emplace<comp::outside_level>(entity);

  return entity;
}

}  // namespace

void load_levels(entt::registry& shared, graphics_context& graphics)
{
  const auto data = parse_world(resources::map("world.json"));
  const auto world = create_world(shared, graphics, data);

  for (const auto& sublevel : data.levels)
  {
    shared.emplace<comp::level>(shared.create(), sys::make_level(sublevel, graphics));
  }

  shared.emplace<comp::active_level>(world);
}

}  // namespace wanderer