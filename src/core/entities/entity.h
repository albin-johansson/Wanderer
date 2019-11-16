#pragma once
#include "movable_object.h"
#include "entity_state_id.h"
#include "input.h"
#include "image.h"
#include <memory>

namespace wanderer::core {

/**
 * The IEntity interface is a subinterface of IMovableObject that specifies objects that are
 * "alive" in the game world.
 *
 * @see IMovableObject
 * @since 0.1.0
 */
class IEntity : public IMovableObject {
 protected:
  IEntity() = default;

 public:
  ~IEntity() override = default;

  /**
   * Handles the supplied input.
   *
   * @param input a reference to the input state.
   * @since 0.1.0
   */
  virtual void HandleInput(const Input& input) = 0; // FIXME this is only used by the player

  /**
   * Sets the entity state that will be used by the entity.
   *
   * @param id the id of the state that will be used.
   * @since 0.1.0
   */
  virtual void SetState(EntityStateID id) = 0;

  /**
   * Returns a reference to the internal tile sheet.
   *
   * @return a reference to the internal tile sheet.
   * @since 0.1.0
   */
  virtual visuals::Image& GetTileSheet() const noexcept = 0;
};

using IEntity_uptr = std::unique_ptr<IEntity>;
using IEntity_sptr = std::shared_ptr<IEntity>;
using IEntity_wptr = std::weak_ptr<IEntity>;

}
