#pragma once
#include <rect.h>

#include <utility>
#include <vector>

#include "vector_2.h"
#include "wanderer_stdinc.h"

namespace wanderer {

/**
 * The Hitbox class represents a hitbox built from rectangles.
 *
 * @since 0.1.0
 */
class Hitbox final {
 public:
  Hitbox();

  ~Hitbox();

  /**
   * Adds a rectangle that will serve as a part of the hitbox.
   *
   * @param rect a rectangle that will serve as a part of the hitbox.
   * @since 0.1.0
   */
  void add_rectangle(const ctn::FRect& rect, const Vector2& offset);

  /**
   * Sets the x-coordinate of the hitbox.
   *
   * @param x the new x-coordinate of the hitbox.
   * @since 0.1.0
   */
  void set_x(float x) noexcept;

  /**
   * Sets the y-coordinate of the hitbox.
   *
   * @param y the new y-coordinate of the hitbox.
   * @since 0.1.0
   */
  void set_y(float y) noexcept;

  /**
   * Sets whether or not the hitbox is enabled. A hitbox that is disabled cannot
   * intersect other hitboxes.
   *
   * @param enabled true if the hitbox should be enabled; false otherwise.
   * @since 0.1.0
   */
  void set_enabled(bool enabled) noexcept;

  /**
   * Indicates whether or not the hitbox only contains one rectangle.
   *
   * @return true if the hitbox is built by only one rectangle; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool is_unit() const noexcept;

  /**
   * Indicates whether or not the supplied hitbox intersects this hitbox.
   *
   * @param other the other hitbox to check.
   * @return true if the hitboxes intersect; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool intersects(const Hitbox& other) const noexcept;

  [[nodiscard]] bool intersects(const ctn::FRect& other) const noexcept;

  [[nodiscard]] bool will_intersect(const Hitbox& other,
                                    const Vector2& nextPos) const noexcept;

  /**
   * Indicates whether or not the hitbox is enabled.
   *
   * @return true if the hitbox is enabled; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool is_enabled() const noexcept;

  /**
   * Returns the rectangle that represents the bounds of the hitbox.
   *
   * @return the rectangle that represents the bounds of the hitbox.
   * @since 0.1.0
   */
  [[nodiscard]] const ctn::FRect& get_bounds() const noexcept;

 private:
  ctn::FRect m_bounds;
  std::vector<std::pair<ctn::FRect, Vector2>> m_rectangles;
  bool m_enabled = false;

  void calc_bounds();
};

}  // namespace wanderer
