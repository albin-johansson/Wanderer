#pragma once
#include "player_state.h"
#include "entity.h"
#include "entity_draw_delegate.h"
#include "entity_idle_delegate.h"

namespace albinjohansson::wanderer {

/**
 * The PlayerIdleState class is an implementation of the IPlayerState interface that represents
 * the state of the player when idle.
 *
 * @see IPlayerState
 * @since 0.1.0
 */
class PlayerIdleState final : public IPlayerState {
 private:
  EntityIdleDelegate idleDelegate;

 public:
  /**
   * @param parent a pointer to the parent entity state machine.
   * @throws NullPointerException if the supplied pointer is null.
   * @since 0.1.0
   */
  explicit PlayerIdleState(IEntityStateMachine* parent);

  ~PlayerIdleState() override;

  void HandleInput(const Input& input, const IWandererCore& core) override;

  void Draw(Renderer& renderer, const Viewport& viewport) const noexcept override;

  void Tick(const IWandererCore& core, float delta) override;

  void Enter(const IWandererCore& core) override;

  void Exit(const IWandererCore& core) override;
};

}
