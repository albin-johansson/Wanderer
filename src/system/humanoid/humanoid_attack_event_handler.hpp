#pragma once

#include "component/event/begin_attack_event.hpp"
#include "component/event/end_attack_event.hpp"
#include "wanderer_stdinc.hpp"

namespace wanderer::sys::humanoid {

/**
 * Handles the event of beginning a humanoid attack sequence.
 *
 * @pre <code>event.registry</code> must not be null.
 * @pre <code>event.sourceEntity</code> must not have a
 * <code>HumanoidAttack</code> component.
 * @param event the event data associated with the start of the attack.
 */
void on_attack_begin(const begin_attack_event& event);

/**
 * Handles the event of beginning a humanoid attack sequence.
 *
 * @pre <code>event.registry</code> must not be null.
 * @pre <code>event.sourceEntity</code> must have a
 * <code>HumanoidAttack</code> component.
 * @param event the event data associated with the end of the attack.
 */
void on_attack_end(const end_attack_event& event);

}  // namespace wanderer::sys::humanoid
