#include "level_switch_animation_system.hpp"

#include <centurion.hpp>

#include "game_constants.hpp"
#include "level_switch_animation.hpp"

namespace wanderer::sys {

void update_level_switch_animations(entt::registry& registry,
                                    entt::dispatcher& dispatcher)
{
  const auto view = registry.view<comp::level_switch_animation>();
  view.each([&](comp::level_switch_animation& animation) {
    if (animation.fadingIn)
    {
      ++animation.step;
      if (animation.step == animation.nSteps - 1)
      {
        dispatcher.enqueue<event::level_faded_in>(animation.map.value(),
                                                  animation.step,
                                                  animation.nSteps,
                                                  animation.hStepSize,
                                                  animation.vStepSize);
      }
    }
    else
    {
      --animation.step;
      if (animation.step == 0)
      {
        dispatcher.enqueue<event::level_faded_out>();
      }
    }
  });
}

void render_level_switch_animations(const entt::registry& registry,
                                    cen::renderer& renderer)
{
  const auto view = registry.view<const comp::level_switch_animation>();
  view.each([&](const comp::level_switch_animation& animation) noexcept {
    constexpr auto logicalSize = glob::logical_size<cen::farea>;
    constexpr auto width = logicalSize.width;
    constexpr auto height = logicalSize.height;

    const auto step = static_cast<float>(animation.step);
    const auto hSize = animation.hStepSize + (step * animation.hStepSize);
    const auto vSize = animation.vStepSize + (step * animation.vStepSize);

    constexpr cen::color gray{0x11, 0x11, 0x11, 0xFF};
    renderer.set_color(gray);

    renderer.fill_rect<float>({{}, {width, vSize}});
    renderer.fill_rect<float>({{0, height - vSize}, {width, vSize}});
    renderer.fill_rect<float>({{}, {hSize, height}});
    renderer.fill_rect<float>({{width - hSize, 0}, {hSize, height}});
  });
}

void start_level_fade_animation(entt::registry& registry, const map_id map)
{
  constexpr auto nSteps = 120.0f;

  const auto entity = registry.create();
  auto& anim = registry.emplace<comp::level_switch_animation>(entity);
  anim.map = map;
  anim.step = 0;
  anim.nSteps = static_cast<int>(nSteps);
  anim.hStepSize = (glob::logical_width<float> / 2.0f) / nSteps;
  anim.vStepSize = (glob::logical_height<float> / 2.0f) / nSteps;
  anim.fadingIn = true;
}

void end_level_fade_animation(entt::registry& registry,
                              const event::level_faded_in& event)
{
  const auto entity = registry.create();
  registry.emplace<comp::level_switch_animation>(entity,
                                                 std::nullopt,
                                                 event.step,
                                                 event.nSteps,
                                                 event.hStepSize,
                                                 event.vStepSize,
                                                 false);
}

}  // namespace wanderer::sys
