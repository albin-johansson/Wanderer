#pragma once

#include "hitbox.h"
#include "vector_2.h"
#include "wanderer_stdinc.h"

namespace wanderer::sys::hitbox {

void update_collision(entt::registry& registry);

/**
 * @brief Updates the bounds of a hitbox.
 *
 * @details Verifies and updates the state of the bounds of a hitbox. The bounds
 * is the bounding rectangle that covers all of the subhitboxes in a hitbox.
 *
 * @param hitbox the hitbox that will be updated.
 */
void update_bounds(comp::Hitbox& hitbox) noexcept;

/**
 * @brief Updates the position of a hitbox.
 *
 * @param hitbox the hitbox that will be moved.
 * @param position the new position of the hitbox.
 */
void update_position(comp::Hitbox& hitbox, const vector2f& position) noexcept;

/**
 * @brief Indicates whether or not two hitboxes intersect.
 *
 * @details Determines whether or not two hitboxes are currently intersecting
 * each other.
 *
 * @note Checking whether or not a hitbox intersects itself will result in the
 * method returning `false`.
 * @code{.cpp}
 * Hitbox hbox = ...;
 * bool res = hitbox::intersects(hbox, hbox); // This will always return false!
 * @endcode
 *
 * @param fst the first hitbox.
 * @param snd the second hitbox.
 * @return `true` if the hitboxes intersect; `false` otherwise.
 */
[[nodiscard]] auto intersects(const comp::Hitbox& fst,
                              const comp::Hitbox& snd) noexcept -> bool;

/**
 * @brief Creates and returns a hitbox.
 * @details This method is for convenience and will update the bounds of the
 * created hitbox before returning it.
 * @param boxes the subhitboxes that will be added to the hitbox.
 * @return a `Hitbox` instance.
 */
[[nodiscard]] inline auto create(std::vector<comp::Subhitbox>&& boxes)
    -> comp::Hitbox
{
  using comp::Hitbox;

  Hitbox hb;
  hb.boxes = std::move(boxes);

  update_bounds(hb);

  return hb;
}

}  // namespace wanderer::sys::hitbox
