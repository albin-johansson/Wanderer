#pragma once

#include <concepts>  // convertible_to
#include <entt.hpp>  // entity, null

namespace wanderer {

// clang-format off

template <typename T>
concept has_entity_member = requires
{
  typename T::entity;
  std::convertible_to<typename T::entity, entt::entity>;
};

// clang-format on

/**
 * \brief Creates and returns a null entity identifier.
 *
 * \pre `T` must have a public entity tag type `T::entity`.
 *
 * \tparam T the type that has a entity tag type.
 *
 * \return a null value of the entity tag type.
 */
template <has_entity_member T>
[[nodiscard]] constexpr auto null() noexcept
{
  return typename T::entity{entt::entity{entt::null}};
}

}  // namespace wanderer
