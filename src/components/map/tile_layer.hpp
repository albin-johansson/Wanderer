#pragma once

#include <vector>

#include "entity_type.hpp"
#include "ints.hpp"
#include "tile_id.hpp"

namespace wanderer::comp {
namespace detail {
struct tile_layer_entity_t;
}

/**
 * \struct tile_layer
 *
 * \brief Represents a layer of tiles.
 *
 * \details Multiple tile layers are combined to create tilemaps.
 *
 * \headerfile tile_layer.hpp
 */
struct tile_layer final
{
  using entity = entity_type<detail::tile_layer_entity_t>;
  using tile_matrix = std::vector<std::vector<tile_id>>;

  tile_matrix matrix;  ///< Matrix of tile IDs that represent the layer.
  int z;               ///< Index that indicates when the layer should be rendered.
};

template <typename Archive>
void serialize(Archive& archive, tile_layer& tl, u32 version)
{
  archive(tl.matrix, tl.z);
}

}  // namespace wanderer::comp
