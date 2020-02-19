#pragma once
#include "direction.h"
#include "entity_move_delegate.h"
#include "entity_state.h"
#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

class IEntityStateMachine;

/**
 * The SkeletonMovingState class represents the state of a moving skeleton.
 *
 * @see IEntityState
 * @since 0.1.0
 */
class SkeletonMovingState final : public IEntityState {
 private:
  EntityMoveDelegate moveDelegate;
  uint32 enterTime = 0;

  void ChasePlayer(const IWandererCore& core, float distance);

  void Roam(const IWandererCore& core);

 public:
  /**
   * @param parent a raw pointer to the parent state machine.
   * @throws NullPointerException if the supplied pointer is null.
   * @since 0.1.0
   */
  explicit SkeletonMovingState(IEntityStateMachine* parent);

  ~SkeletonMovingState() override;

  void tick(const IWandererCore& core, float delta) override;

  void draw(const centurion::video::Renderer& renderer,
            const Viewport& viewport) const override;

  void enter(const IWandererCore& core) override;

  void exit(const IWandererCore& core) override;
};

}  // namespace albinjohansson::wanderer
