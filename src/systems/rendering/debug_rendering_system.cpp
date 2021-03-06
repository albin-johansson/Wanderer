#include "debug_rendering_system.hpp"

#include "active_menu.hpp"
#include "centurion_utils.hpp"
#include "chase.hpp"
#include "container_trigger.hpp"
#include "depth_drawable.hpp"
#include "hitbox.hpp"
#include "menu_constants.hpp"
#include "menu_system.hpp"
#include "player.hpp"
#include "portal.hpp"

namespace wanderer::sys {
namespace {

void render_hitboxes(const entt::registry& registry, cen::renderer& renderer)
{
  const auto view = registry.view<const comp::hitbox>();
  view.each([&](const entt::entity entity, const comp::hitbox& hitbox) {
    if (registry.has<comp::portal>(entity) ||
        registry.has<comp::container_trigger>(entity))
    {
      renderer.set_color(cen::colors::cyan);
    }
    else
    {
      renderer.set_color(cen::colors::lime);
    }

    for (const auto& [offset, size] : hitbox.boxes)
    {
      const cen::frect rect{to_point(hitbox.origin + offset), size};

      renderer.set_color(renderer.get_color().with_alpha(100));
      renderer.draw_rect_t(rect);
    }

    renderer.set_color(renderer.get_color().with_alpha(255));
    renderer.draw_rect_t(hitbox.bounds);
  });
}

void render_enabled_trigger_indicator(const entt::registry& registry,
                                      const entt::entity entity,
                                      cen::renderer& renderer)
{
  assert(registry.has<comp::hitbox>(entity));
  const auto& hitbox = registry.get<comp::hitbox>(entity);

  renderer.set_color(cen::colors::cyan.with_alpha(100));
  renderer.fill_rect_t(hitbox.bounds);
}

void render_trigger_indicators(const entt::registry& registry, cen::renderer& renderer)
{
  const auto entity = registry.ctx<ctx::player>().entity;
  if (const auto* iwp = registry.try_get<comp::is_within_portal>(entity))
  {
    render_enabled_trigger_indicator(registry, iwp->portalEntity, renderer);
  }
  else if (const auto* iwc = registry.try_get<comp::is_within_container_trigger>(entity))
  {
    render_enabled_trigger_indicator(registry, iwc->triggerEntity, renderer);
  }
}

void render_chase_ranges(const entt::registry& registry, cen::renderer& renderer)
{
  renderer.set_color(cen::colors::red);

  const auto view = registry.view<const comp::depth_drawable, const comp::chase>();
  view.each([&](const comp::depth_drawable& drawable, const comp::chase& chase) {
    renderer.draw_circle_t(drawable.dst.center(), chase.range);
  });
}

}  // namespace

void render_debug_info(const entt::registry& registry, graphics_context& graphics)
{
  auto& renderer = graphics.renderer();
  render_hitboxes(registry, renderer);
  render_trigger_indicators(registry, renderer);
  render_chase_ranges(registry, renderer);
}

void render_menu_debug_info(const entt::registry& registry, graphics_context& graphics)
{
  auto& renderer = graphics.renderer();

  const auto menuEntity = registry.ctx<ctx::active_menu>().entity;
  const auto& menu = registry.get<comp::menu>(menuEntity);

  if (menu.id != menu_id::in_game)
  {
    renderer.set_color(cen::colors::light_gray.with_alpha(50));

    const auto endX = glob::logical_width<>;
    const auto endY = glob::logical_height<>;

    for (auto row = 0; row < glob::menu_rows; ++row)
    {
      const auto y = row * glob::menu_row_size;
      renderer.draw_line<int>({0, y}, {endX, y});
    }

    for (auto col = 0; col < glob::menu_columns; ++col)
    {
      const auto x = col * glob::menu_col_size;
      renderer.draw_line<int>({x, 0}, {x, endY});
    }

    renderer.draw_line<int>({0, endY - 1}, {endX, endY - 1});
    renderer.draw_line<int>({endX - 1, 0}, {endX - 1, endY});
  }
}

}  // namespace wanderer::sys
