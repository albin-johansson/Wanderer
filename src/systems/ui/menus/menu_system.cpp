#include "menu_system.hpp"

#include "components/ctx/active_menu.hpp"
#include "components/ctx/cursors.hpp"
#include "components/ui/associated_menu.hpp"
#include "events/button_pressed_event.hpp"
#include "systems/ui/buttons/button_system.hpp"
#include "systems/ui/menus/saves/saves_menu_system.hpp"

namespace wanderer::sys {

void update_menu(entt::registry& registry,
                 entt::dispatcher& dispatcher,
                 const input& input)
{
  const auto menuEntity = registry.ctx<ctx::active_menu>().entity;
  const auto& menu = registry.get<comp::menu>(menuEntity);

  if (const auto button = update_button_hover(registry, input.mouse))
  {
    if (query_button(registry, dispatcher, *button, input.mouse))
    {
      if (auto* group = registry.try_get<comp::button_group>(menuEntity))
      {
        if (sys::in_button_group(group->buttons, *button))
        {
          group->selected = *button;
        }
      }
    }
  }
  else
  {
    cen::cursor::reset();
  }

  for (auto&& [entity, bind, associated] :
       registry.view<comp::key_bind, comp::associated_menu>().each())
  {
    if (associated.entity == menuEntity && input.keyboard.just_released(bind.key))
    {
      dispatcher.enqueue<button_pressed_event>(bind.action);
    }
  }
}

void switch_menu(entt::registry& registry, const menu_id id)
{
  registry.unset<ctx::active_menu>();

  for (auto&& [entity, menu] : registry.view<comp::menu>().each())
  {
    if (menu.id == id)
    {
      registry.set<ctx::active_menu>(comp::menu::entity{entity});

      if (menu.id == menu_id::saves)
      {
        on_saves_menu_enabled(registry);
      }
    }
  }
}

auto is_current_menu_blocking(const entt::registry& registry) -> bool
{
  const auto menuEntity = registry.ctx<const ctx::active_menu>().entity;
  return registry.get<comp::menu>(menuEntity).blocking;
}

}  // namespace wanderer::sys
