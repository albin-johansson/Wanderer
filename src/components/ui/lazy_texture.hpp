#pragma once

#include <centurion.hpp>  // farea, surface, texture

#include "core/aliases/entity_type.hpp"
#include "core/aliases/maybe.hpp"

namespace wanderer::comp {
namespace detail {
struct lazy_texture_t;
}

/**
 * \brief Represents a texture that is lazily initialized.
 *
 * \ingroup components
 */
struct lazy_texture final
{
  using entity = entity_type<detail::lazy_texture_t>;

  float row;                            ///< The row value.
  float col;                            ///< The column value.
  cen::farea size;                      ///< The size of the rendered texture.
  cen::surface surface;                 ///< Source image data.
  mutable maybe<cen::texture> texture;  ///< The lazily initialized texture.
};

}  // namespace wanderer::comp
