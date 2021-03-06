#pragma once

#include <entt.hpp>  // entity, null

#include "ints.hpp"

namespace wanderer::ctx {

/**
 * \struct player
 *
 * \brief A tag type used to identify the player.
 *
 * \headerfile player.hpp
 */
struct player final
{
  entt::entity entity{entt::null};
};

template <typename Archive>
void serialize(Archive& archive, player& p, u32 version)
{
  archive(p.entity);
}

}  // namespace wanderer::ctx