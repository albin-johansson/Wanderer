#include "graphics_context.hpp"

#include "make_renderer.hpp"
#include "resources.hpp"

namespace wanderer {

graphics_context::graphics_context(const cen::window& window)
    : m_renderer{make_renderer(window)}
    , m_format{window.get_pixel_format()}
    , m_smallFontCache{resources::font("type_writer.ttf"), 8}
{
  m_textures.reserve(10);

  m_renderer.set_color(cen::colors::white);
  m_smallFontCache.add_latin1(m_renderer);
}

void graphics_context::render(const texture_index index,
                              const cen::irect& src,
                              const cen::frect& dst) noexcept
{
  const auto& texture = find(index);
  m_renderer.render_t(texture, src, dst);
}

auto graphics_context::load(const texture_id id, const std::string& path) -> texture_index
{
  if (const auto it = m_identifiers.find(id); it != m_identifiers.end())
  {
    return it->second;
  }

  const auto index = m_textures.size();

  m_textures.emplace_back(m_renderer, path);
  m_identifiers.try_emplace(id, index);

  return texture_index{index};
}

auto graphics_context::to_index(const texture_id id) const -> texture_index
{
  return m_identifiers.at(id);
}

auto graphics_context::find(const texture_index index) const noexcept
    -> const cen::texture&
{
  assert(index < m_textures.size());
  return m_textures[index];
}

}  // namespace wanderer
