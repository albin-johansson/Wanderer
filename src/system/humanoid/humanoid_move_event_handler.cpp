#include "humanoid_move_event_handler.hpp"

#include "humanoid_animation_system.hpp"
#include "humanoid_state.hpp"

using wanderer::comp::HumanoidIdle;
using wanderer::comp::HumanoidMove;

namespace wanderer::sys::humanoid {

void on_move_begin(const BeginHumanoidMoveEvent& event)
{
  assert(event.registry != nullptr);
  assert(!event.registry->has<HumanoidMove>(event.entity));

  const auto entity = event.entity;

  event.registry->emplace<HumanoidMove>(entity);

  humanoid::enter_move_animation(*event.registry, entity, event.direction);
}

void on_move_end(const EndHumanoidMoveEvent& event)
{
  assert(event.registry != nullptr);
  assert(event.registry->has<HumanoidMove>(event.entity));

  const auto entity = event.entity;

  //  event.registry->remove<HumanoidMove>(entity);
  event.registry->emplace<HumanoidIdle>(entity);
  assert(!event.registry->has<HumanoidMove>(entity));

  humanoid::enter_idle_animation(*event.registry, entity);
}

}  // namespace wanderer::sys::humanoid
