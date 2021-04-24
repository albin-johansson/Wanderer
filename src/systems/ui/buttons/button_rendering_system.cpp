#include "button_rendering_system.hpp"

#include "core/graphics/render_text.hpp"
#include "core/menu_constants.hpp"
#include "systems/ui/grid.hpp"

namespace wanderer::sys {
namespace {

inline constexpr auto button_outline_fg_color = cen::colors::ghost_white;
inline constexpr auto button_outline_bg_color = button_outline_fg_color.with_alpha(0x22);
inline constexpr auto button_font = glob::menu_font_m;

void update_bounds(const comp::button& button,
                   cen::frect& bounds,
                   cen::renderer& renderer)
{
  const auto& font = renderer.get_font(button_font);
  const auto [width, height] = font.string_size(button.text).value();

  const auto pos = from_grid(button.position);
  bounds.set_size({width * 1.25f, height * 1.5f});
  bounds.set_x(pos.x() - (bounds.width() / 2.0f));
  bounds.set_y(pos.y() + ((glob::menu_row_size - bounds.height()) / 2.0f));
}

void init_text(const comp::button_drawable& drawable,
               const std::string& text,
               cen::renderer& renderer)
{
  const auto& font = renderer.get_font(button_font);

  renderer.set_color(cen::colors::white);
  drawable.texture.emplace(render_text(renderer, text, font));
}

void render_text(const comp::button& button,
                 const comp::button_drawable& drawable,
                 cen::renderer& renderer)
{
  if (button.text.empty())
  {
    return;
  }

  if (!drawable.textPos)
  {
    const auto& font = renderer.get_font(button_font);
    const auto [width, height] = font.string_size(button.text).value();
    drawable.textPos = {drawable.bounds.center_x() - (width / 2.0f),
                        drawable.bounds.center_y() - (height / 2.0f)};
  }

  auto& texture = drawable.texture.value();
  texture.set_alpha(button.enabled ? 255 : 100);

  renderer.render(texture, *drawable.textPos);
  texture.set_alpha(255);
}

void render_outline(const comp::button_drawable& drawable, cen::renderer& renderer)
{
  renderer.set_color(button_outline_bg_color);
  renderer.fill_rect(drawable.bounds);

  renderer.set_color(button_outline_fg_color);
  renderer.draw_rect(drawable.bounds);
}

void render_button(const entt::registry& registry,
                   graphics_context& graphics,
                   const comp::button::entity buttonEntity)
{
  auto& renderer = graphics.renderer();
  const auto& button = registry.get<comp::button>(buttonEntity);
  const auto& drawable = registry.get<comp::button_drawable>(buttonEntity);

  if (!button.visible)
  {
    return;
  }

  if (!drawable.texture)
  {
    update_bounds(button, drawable.bounds, renderer);
    init_text(drawable, button.text, renderer);
  }

  if (button.hover && button.enabled)
  {
    render_outline(drawable, renderer);
  }

  render_text(button, drawable, renderer);
}

}  // namespace

void render_buttons(const entt::registry& registry,
                    graphics_context& graphics,
                    const comp::button_pack& pack)
{
  for (const auto entity : pack.buttons)
  {
    render_button(registry, graphics, entity);
  }
}

void render_button_group(const entt::registry& registry,
                         graphics_context& graphics,
                         const comp::button_group& group)
{
  if (group.selected != entt::null)
  {
    auto& renderer = graphics.renderer();
    const auto& button = registry.get<comp::button>(group.selected);
    const auto& drawable = registry.get<comp::button_drawable>(group.selected);
    renderer.set_color(cen::colors::dark_green);
    renderer.fill_rect(drawable.bounds);
  }

  for (const auto entity : group.buttons)
  {
    render_button(registry, graphics, entity);
  }
}

}  // namespace wanderer::sys