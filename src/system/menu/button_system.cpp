#include "button_system.hpp"

#include "cursors.hpp"
#include "game_constants.hpp"
#include "menu_constants.hpp"
#include "registry_utils.hpp"

namespace wanderer::sys {
namespace {

void update_bounds(const comp::button& button,
                   const comp::button_drawable& drawable,
                   cen::renderer& renderer)
{
  auto& bounds = drawable.bounds;

  auto& font = renderer.get_font(glob::menuSmallFont);
  const auto [width, height] = font.string_size(button.text.c_str());
  bounds.set_size({width * 1.25f, height * 1.75f});

  const auto calcX = [&]() -> int {
    const auto width = static_cast<int>(bounds.width());

    // make button centered if column index is -1
    if (button.col == -1) {
      return (glob::logicalWidth<int> / 2) - (width / 2);
    } else {
      return (button.col * glob::menuColSize) - (width / 2);
    }
  };

  const auto y = static_cast<float>(button.row * glob::menuRowSize) -
                 (bounds.height() / 2.0f);

  bounds.set_x(static_cast<float>(calcX()));
  bounds.set_y(y);
}

[[nodiscard]] auto to_texture(cen::renderer& renderer,
                              const std::string& text,
                              const cen::font& font) -> cen::texture
{
  return renderer.render_blended_utf8(text.c_str(), font);
}

void init_text(const comp::button_drawable& drawable,
               const std::string& text,
               cen::renderer& renderer)
{
  const auto& font = renderer.get_font(glob::menuSmallFont);

  renderer.set_color(cen::colors::white);
  drawable.texture.emplace(to_texture(renderer, text, font));
}

void render_text(const comp::button& button,
                 const comp::button_drawable& drawable,
                 cen::renderer& renderer)
{
  if (button.text.empty()) {
    return;
  }

  if (!drawable.textPos) {
    const auto& font = renderer.get_font(glob::menuSmallFont);
    const auto [width, height] = font.string_size(button.text.c_str());
    const auto x = drawable.bounds.center_x() - (width / 2.0f);
    const auto y = drawable.bounds.center_y() - (height / 2.0f);
    drawable.textPos = {x, y};
  }

  renderer.render(drawable.texture.value(), *drawable.textPos);
}

void render_background(const comp::button_drawable& drawable,
                       cen::renderer& renderer)
{
  constexpr auto bg = cen::colors::ghost_white.with_alpha(0x22);

  renderer.set_color(bg);
  renderer.fill_rect(drawable.bounds);

  renderer.set_color(cen::colors::ghost_white);
  renderer.draw_rect(drawable.bounds);
}

}  // namespace

auto query_button(entt::registry& registry,
                  entt::dispatcher& dispatcher,
                  const cen::mouse_state& mouseState,
                  const comp::button::entity buttonEntity) -> bool
{
  const auto& button = registry.get<comp::button>(buttonEntity);

  if (button.hover) {
    auto& cursors = singleton<comp::cursors>(registry);
    cursors.data.at(cen::system_cursor::hand).enable();
  }

  if (button.hover && mouseState.was_left_button_released()) {
    if (button.action) {
      button.action->execute(dispatcher);
      cen::cursor::reset();
      return true;
    }
  }

  return false;
}

auto update_button_hover(entt::registry& registry,
                         const comp::menu::entity menuEntity,
                         const cen::mouse_state& mouseState)
    -> maybe<comp::button::entity>
{
  maybe<comp::button::entity> hoverButton;
  const auto mousePos = cen::cast<cen::fpoint>(mouseState.mouse_pos());

  const auto& menu = registry.get<comp::menu>(menuEntity);
  for (const auto entity : menu.buttons) {
    auto& button = registry.get<comp::button>(entity);
    const auto& drawable = registry.get<comp::button_drawable>(entity);

    button.hover = drawable.bounds.contains(mousePos);
    if (button.hover) {
      hoverButton = entity;
    }
  }

  return hoverButton;
}

void render_button(const entt::registry& registry,
                   cen::renderer& renderer,
                   const comp::button::entity buttonEntity)
{
  const auto& button = registry.get<comp::button>(buttonEntity);
  auto& drawable = registry.get<comp::button_drawable>(buttonEntity);

  if (!drawable.texture) {
    update_bounds(button, drawable, renderer);
    init_text(drawable, button.text, renderer);
  }

  if (button.hover) {
    render_background(drawable, renderer);
  }

  render_text(button, drawable, renderer);
}

}  // namespace wanderer::sys
