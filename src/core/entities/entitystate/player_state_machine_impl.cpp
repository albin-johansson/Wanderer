#include "player_state_machine_impl.h"
#include "objects.h"
#include "player_moving_state.h"
#include "player_idle_state.h"
#include "player_attack_state.h"
#include "player_dying_state.h"

using namespace wanderer::visuals;

namespace wanderer::core {

PlayerStateMachineImpl::PlayerStateMachineImpl(IEntity* entity) {
  this->entity = Objects::RequireNonNull(entity);

  Put(EntityStateID::IDLE, std::make_unique<PlayerIdleState>(this));
  Put(EntityStateID::DIE, std::make_unique<PlayerDyingState>(entity));
  Put(EntityStateID::WALK, std::make_unique<PlayerMovingState>(this));
  Put(EntityStateID::ATTACK, std::make_unique<PlayerAttackState>(this));

  activeStateID = EntityStateID::IDLE;
}

PlayerStateMachineImpl::~PlayerStateMachineImpl() = default;

IPlayerStateMachine_uptr PlayerStateMachineImpl::Create(IEntity* entity) {
  return std::make_unique<PlayerStateMachineImpl>(entity);
}

void PlayerStateMachineImpl::Put(EntityStateID id, IPlayerState_uptr state) {
  states.insert(std::pair<EntityStateID, IPlayerState_uptr>(id, std::move(state)));
}

void PlayerStateMachineImpl::HandleInput(const Input& input, const IGame& game) {
  states.at(activeStateID)->HandleInput(input, game);
}

void PlayerStateMachineImpl::SetState(EntityStateID id, const IGame& game) {
  states.at(activeStateID)->Exit(game);

  activeStateID = id;
  states.at(activeStateID)->Enter(game);
}

void PlayerStateMachineImpl::Tick(const IGame& w, float delta) {
  states.at(activeStateID)->Tick(w, delta);
}

void PlayerStateMachineImpl::Draw(Renderer& renderer, const Viewport& viewport) const noexcept {
  states.at(activeStateID)->Draw(renderer, viewport);
}

IEntity& PlayerStateMachineImpl::GetEntity() {
  return *entity;
}

}
