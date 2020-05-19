#include "player_idle_state.h"

#include "entity.h"
#include "entity_state_machine.h"
#include "input.h"

using namespace centurion;

namespace wanderer {

PlayerIdleState::PlayerIdleState(IEntityStateMachine* parent)
    : idleDelegate{parent}
{}

PlayerIdleState::~PlayerIdleState() = default;

void PlayerIdleState::HandleInput(const Input& input, const IWandererCore& core)
{
  if (input.is_pressed(SDL_SCANCODE_D) || input.is_pressed(SDL_SCANCODE_A) ||
      input.is_pressed(SDL_SCANCODE_W) || input.is_pressed(SDL_SCANCODE_S)) {
    idleDelegate.get_parent().set_state(EntityStateID::Walk, core);
  } else if (input.is_pressed(SDL_SCANCODE_SPACE)) {
    idleDelegate.get_parent().set_state(EntityStateID::Attack, core);
  } else if (input.is_pressed(SDL_SCANCODE_U)) {
    idleDelegate.get_parent().set_state(EntityStateID::Die, core);
  }

  // TODO attack...
}

void PlayerIdleState::draw(Renderer& renderer,
                           const Viewport& viewport) const noexcept
{
  idleDelegate.draw(renderer, viewport);
}

void PlayerIdleState::tick(const IWandererCore& core, float delta)
{
  idleDelegate.tick(core, delta);
}

void PlayerIdleState::enter(const IWandererCore& core)
{
  idleDelegate.enter(core);
}

void PlayerIdleState::exit(const IWandererCore& core)
{
  idleDelegate.exit(core);
}

}  // namespace wanderer
