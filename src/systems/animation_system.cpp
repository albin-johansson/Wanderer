#include "animation_system.hpp"

#include <centurion.hpp>

#include "animated.hpp"

namespace wanderer::sys {

void update_animations(entt::registry& registry) noexcept
{
  registry.view<comp::animated>().each([](comp::animated& animated) {
    const auto now = cen::counter::ticks();
    const auto elapsed = now - animated.then;
    if (elapsed >= animated.delay)
    {
      animated.then = now;
      ++animated.frame;
      if (animated.frame >= animated.nFrames)
      {
        animated.frame = 0;
      }
    }
  });
}

}  // namespace wanderer::sys
