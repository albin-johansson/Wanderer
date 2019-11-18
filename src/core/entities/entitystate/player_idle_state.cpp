#include "player_idle_state.h"
#include "entity_state_machine.h"

namespace wanderer::core {

PlayerIdleState::PlayerIdleState(IEntity* entity, IEntityStateMachine* parent)
    : idleDelegate(EntityIdleDelegate(entity, parent)) {}

PlayerIdleState::~PlayerIdleState() = default;

void PlayerIdleState::HandleInput(const Input& input) {
  if (input.IsPressed(SDL_SCANCODE_D)
      || input.IsPressed(SDL_SCANCODE_A)
      || input.IsPressed(SDL_SCANCODE_W)
      || input.IsPressed(SDL_SCANCODE_S)) {
    idleDelegate.GetParent()->Change(EntityStateID::WALK);
  } else if (input.IsPressed(SDL_SCANCODE_SPACE)) {
    idleDelegate.GetParent()->Change(EntityStateID::ATTACK);
  } else if (input.IsPressed(SDL_SCANCODE_U)) {
    idleDelegate.GetParent()->Change(EntityStateID::DIE);
  }

  // TODO attack...
}

}