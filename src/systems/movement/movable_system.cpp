#include "movable_system.hpp"

#include "maybe.hpp"

namespace wanderer::sys {
namespace {

auto horizontal_dominant_direction(const comp::movable& movable) noexcept
    -> maybe<direction>
{
  if (movable.velocity.x < 0)
  {
    return direction::left;
  }
  else if (movable.velocity.x > 0)
  {
    return direction::right;
  }
  else
  {
    return std::nullopt;
  }
}

auto vertical_dominant_direction(const comp::movable& movable) noexcept
    -> maybe<direction>
{
  if (movable.velocity.y < 0)
  {
    return direction::up;
  }
  else if (movable.velocity.y > 0)
  {
    return direction::down;
  }
  else
  {
    return std::nullopt;
  }
}

}  // namespace

auto dominant_direction(const comp::movable& movable) noexcept -> direction
{
  if (const auto horizontal = horizontal_dominant_direction(movable))
  {
    return *horizontal;
  }

  if (const auto vertical = vertical_dominant_direction(movable))
  {
    return *vertical;
  }

  return movable.dir;
}

}  // namespace wanderer::sys
