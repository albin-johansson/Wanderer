#pragma once
#include "tickable.h"
#include "drawable.h"
#include "input.h"
#include <memory>

namespace wanderer::core {

/**
 * The IEntityState interface specifies .
 *
 * @since 0.1.0
 */
class IEntityState : public ITickable, public IDrawable {
 protected:
  IEntityState() = default;

 public:
  ~IEntityState() override = default;

  /**
   * Reacts to the supplied input
   *
   * @param input a reference to the input state.
   * @since 0.1.0
   */
  virtual void HandleInput(const Input& input) = 0;

  /**
   * Enters the entity state.
   *
   * @since 0.1.0
   */
  virtual void EnterState() = 0;

  /**
   * Exits the entity state.
   *
   * @since 0.1.0
   */
  virtual void ExitState() = 0;

};

using IEntityState_uptr = std::unique_ptr<IEntityState>;
using IEntityState_sptr = std::shared_ptr<IEntityState>;
using IEntityState_wptr = std::weak_ptr<IEntityState>;

}