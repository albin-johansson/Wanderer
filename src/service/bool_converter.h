#pragma once
#include <SDL.h>

namespace wanderer::util {

/**
 * The BoolConverter class is a service for converting C++ boolean values to the
 * corresponding SDL_bool enum values.
 *
 * @since 0.1.0
 */
class BoolConverter final {
 public:
  BoolConverter() = delete;

  ~BoolConverter() = default;

  /**
   * Returns the corresponding SDL_bool value for the supplied boolean value.
   *
   * @param b the boolean value that will be converted.
   * @return the corresponding SDL_bool value for the supplied boolean value.
   * @since 0.1.0
   */
  [[nodiscard]] inline static SDL_bool Convert(bool b) noexcept {
    return (b) ? SDL_TRUE : SDL_FALSE;
  }
};

}  // namespace wanderer::util