#pragma once
#include "player_state.h"
#include "entity_attack_delegate.h"

namespace albinjohansson::wanderer {

class IWandererCore;
class IEntityStateMachine;

/**
 * The PlayerAttackState class is an implementation of the IPlayerState interface that represents
 * the state of the player when attacking.
 *
 * @see IPlayerState
 * @since 0.1.0
 */
class PlayerAttackState final : public IPlayerState {
 private:
  EntityAttackDelegate attackDelegate;

 public:
  /**
   * @param parent a pointer to the parent state machine.
   * @throws NullPointerException if the supplied pointer is null.
   * @since 0.1.0
   */
  explicit PlayerAttackState(IEntityStateMachine* parent);

  ~PlayerAttackState() override;

  void HandleInput(const Input& input, const IWandererCore& core) override;

  void Draw(Renderer& renderer, const Viewport& viewport) const override;

  void Tick(const IWandererCore& core, float delta) override;

  void Enter(const IWandererCore& core) override;

  void Exit(const IWandererCore& core) override;

};

}