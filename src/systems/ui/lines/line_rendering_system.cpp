#include "line_rendering_system.hpp"

#include "systems/ui/grid.hpp"

namespace wanderer::sys {

void render_lines(const entt::registry& registry,
                  graphics_context& graphics,
                  const comp::line_pack& pack)
{
  auto& renderer = graphics.renderer();
  renderer.set_color(cen::colors::white);

  for (const auto entity : pack.lines)
  {
    const auto& line = registry.get<comp::line>(entity);
    renderer.draw_line(from_grid(line.start), from_grid(line.end));
  }
}

}  // namespace wanderer::sys
