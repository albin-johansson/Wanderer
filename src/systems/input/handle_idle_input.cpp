#include <cassert>   // assert
#include <optional>  // optional

#include "begin_attack_event.hpp"
#include "begin_humanoid_move_event.hpp"
#include "binds.hpp"
#include "direction.hpp"
#include "humanoid_state.hpp"
#include "input_system.hpp"
#include "interact_event.hpp"
#include "inventory.hpp"
#include "player.hpp"

namespace wanderer::sys {
namespace {

[[nodiscard]] auto get_direction(const cen::keyboard& keyboard,
                                 const ctx::binds& binds) noexcept
    -> std::optional<direction>
{
  const auto left = keyboard.is_pressed(binds.left);
  const auto right = keyboard.is_pressed(binds.right);
  const auto up = keyboard.is_pressed(binds.up);
  const auto down = keyboard.is_pressed(binds.down);

  if (left)
  {
    return direction::left;
  }
  else if (right)
  {
    return direction::right;
  }
  else if (up)
  {
    return direction::up;
  }
  else if (down)
  {
    return direction::down;
  }
  else
  {
    return std::nullopt;
  }
}

void check_for_movement(entt::registry& registry,
                        entt::dispatcher& dispatcher,
                        const cen::keyboard& keyboard,
                        const ctx::binds& binds)
{
  if (const auto dir = get_direction(keyboard, binds))
  {
    const auto player = registry.ctx<ctx::player>().entity;
    dispatcher.enqueue<event::begin_humanoid_move>(&registry, player, *dir);
  }
}

}  // namespace

void handle_idle_input(entt::registry& registry,
                       entt::dispatcher& dispatcher,
                       const input& input,
                       const ctx::binds& binds)
{
  const auto player = registry.ctx<ctx::player>().entity;

  assert(registry.has<comp::humanoid_idle>(player));
  const auto& keyboard = input.keyboard;

  if (keyboard.just_released(binds.interact))
  {
    dispatcher.enqueue<event::interact>(&registry, &dispatcher);
  }
  else if (registry.empty<comp::active_inventory>())
  {
    if (keyboard.is_pressed(binds.attack))
    {
      // FIXME
      dispatcher.enqueue<event::begin_attack>(&registry,
                                              player,
                                              entt::null,
                                              direction::down);
    }
    else
    {
      check_for_movement(registry, dispatcher, input.keyboard, binds);
    }
  }
}

}  // namespace wanderer::sys
