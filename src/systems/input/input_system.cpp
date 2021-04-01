#include "input_system.hpp"

#include "humanoid_state.hpp"

namespace wanderer::sys {

void update_input(entt::registry& registry,
                  entt::dispatcher& dispatcher,
                  const input& input,
                  const comp::binds& binds)
{
  const auto player = registry.ctx<comp::player>().playerEntity;
  if (registry.has<comp::humanoid_idle>(player))
  {
    handle_idle_input(registry, dispatcher, input, binds);
  }
  else if (registry.has<comp::humanoid_move>(player))
  {
    handle_move_input(registry, dispatcher, input, binds);
  }
}

}  // namespace wanderer::sys
