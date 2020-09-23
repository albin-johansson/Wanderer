/**
 * This file declares all functions related to handling humanoid movement
 * events.
 *
 * @file humanoid_move_event_handler.hpp
 */

#pragma once

#include "begin_humanoid_move_event.hpp"
#include "end_humanoid_move_event.hpp"

namespace wanderer::sys::humanoid {

/**
 * Handles the event of beginning the movement of a humanoid.
 *
 * @pre <code>event.registry</code> must not be null.
 * @pre <code>event.entity</code> must not have a <code>HumanoidMove</code>
 * component.
 * @param event the data for the event.
 */
void on_move_begin(const BeginHumanoidMoveEvent& event);

/**
 * Handles the event of ending the movement of a humanoid.
 *
 * @pre <code>event.registry</code> must not be null.
 * @pre <code>event.entity</code> must have a <code>HumanoidMove</code>
 * component.
 * @param event the data for the event.
 */
void on_move_end(const EndHumanoidMoveEvent& event);

}  // namespace wanderer::sys::humanoid
