#pragma once
#include "player_state.h"
#include "entity.h"
#include "entity_draw_delegate.h"
#include "entity_idle_delegate.h"

namespace wanderer::core {

class PlayerIdleState final : public IPlayerState {
 private:
  EntityIdleDelegate idleDelegate;

 public:
  /**
   * @param parent a pointer to the parent entity state machine.
   * @throws NullPointerException if the supplied pointer is null.
   * @since 0.1.0
   */
  explicit PlayerIdleState(IEntity* entity, IEntityStateMachine* parent);

  ~PlayerIdleState() override;

  void HandleInput(const Input& input) override;

  inline void Draw(visuals::Renderer& renderer, const Viewport& viewport) noexcept override {
    idleDelegate.Draw(renderer, viewport);
  }

  inline void Tick(float delta) override { idleDelegate.Tick(delta); }

  inline void Enter() override { idleDelegate.Enter(); }

  inline void Exit() override { idleDelegate.Exit(); }
};

}