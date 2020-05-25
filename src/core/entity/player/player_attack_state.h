#pragma once
#include "entity_attack_delegate.h"
#include "player_state.h"

namespace wanderer {

class IWandererCore;
class IEntityStateMachine;

/**
 * The PlayerAttackState class is an implementation of the IPlayerState
 * interface that represents the state of the player when attacking.
 *
 * @see IPlayerState
 * @since 0.1.0
 */
class PlayerAttackState final : public IPlayerState {
 public:
  /**
   * @param parent a pointer to the parent state machine.
   * @throws NullPointerException if the supplied pointer is null.
   * @since 0.1.0
   */
  explicit PlayerAttackState(IEntityStateMachine* parent);

  ~PlayerAttackState() override;

  void handle_input(const Input& input, const IWandererCore& core) override;

  void draw(ctn::Renderer& renderer, const Viewport& viewport) const override;

  void tick(const IWandererCore& core, float delta) override;

  void enter(const IWandererCore& core) override;

  void exit(const IWandererCore& core) override;

 private:
  EntityAttackDelegate m_attackDelegate;
};

}  // namespace wanderer