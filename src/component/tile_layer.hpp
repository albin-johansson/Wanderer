/**
 * @brief Provides the `TileLayer` component.
 * @file tile_layer.hpp
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include <named_type.hpp>
#include <vector>

#include "wanderer_stdinc.hpp"

namespace wanderer::comp {

/**
 * @brief Represents a layer of tiles.
 * @details Multiple tile layers are combined to create tilemaps.
 * @struct TileLayer
 * @headerfile tile_layer.hpp
 */
struct TileLayer final {
  using entity = fluent::
      NamedType<entt::entity, struct TileLayerEntityTag, fluent::Comparable>;
  using tile_matrix = std::vector<std::vector<tile_id>>;

  tile_matrix matrix; /**< Matrix of tile IDs that represent the layer. */
};

}  // namespace wanderer::comp
