#include "skeleton_attack_state.h"

namespace wanderer::core {

SkeletonAttackState::SkeletonAttackState(IEntityStateMachine* parent)
    : attackDelegate(EntityAttackDelegate(parent)) {}

SkeletonAttackState::~SkeletonAttackState() = default;

void SkeletonAttackState::Draw(visuals::Renderer& renderer, const Viewport& viewport) const {
  attackDelegate.Draw(renderer, viewport);
}

void SkeletonAttackState::Enter(const IGame& game) {
  attackDelegate.Enter(game);
}

void SkeletonAttackState::Exit(const IGame& game) {
  attackDelegate.Exit(game);
}

void SkeletonAttackState::Tick(const IGame& game, float delta) {
  attackDelegate.Tick(game, delta);
}

}