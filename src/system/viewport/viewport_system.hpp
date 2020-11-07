#pragma once

#include <cen/renderer.hpp>

#include "component/viewport.hpp"
#include "delta.hpp"
#include "level.hpp"

namespace wanderer::sys::viewport {

/**
 * \brief Updates the position of the viewport by slowly tracking a movable
 * entity.
 *
 * \pre `playerEntity` must have a `Movable` component.
 *
 * \param level the level associated with the viewport that will be updated.
 * \param movableEntity the entity ID for the movable.
 * \param dt the delta time, in seconds.
 */
void update(level& level, entt::entity movableEntity, delta dt);

void translate(entt::registry& registry,
               comp::viewport::entity viewportEntity,
               cen::renderer& renderer);

}  // namespace wanderer::sys::viewport
