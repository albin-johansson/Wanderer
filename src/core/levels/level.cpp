#include "level.hpp"

#include <fstream>  // ifstream, ofstream

#include "add_ground_layers.hpp"
#include "add_objects.hpp"
#include "add_tile_objects.hpp"
#include "centurion_utils.hpp"
#include "create_tilemap.hpp"
#include "create_tileset.hpp"
#include "depth_drawables_system.hpp"
#include "humanoid_factory_system.hpp"
#include "humanoid_state.hpp"
#include "make_registry.hpp"
#include "render_bounds_system.hpp"
#include "saves_system.hpp"
#include "serialization.hpp"
#include "viewport_system.hpp"

namespace wanderer {

level::level(const ir::level& data, graphics_context& graphics)
    : m_registry{make_registry()}
    , m_tilemap{m_registry.create()}
    , m_playerSpawnPosition{data.playerSpawnPoint}
{
  m_tree.set_thickness_factor(std::nullopt);

  load_tileset_textures(data, graphics);
  auto& tileset = create_tileset(data.tilesets, m_registry, graphics);
  auto& tilemap = create_tilemap(data, m_registry, m_tilemap);

  m_registry.set<ctx::viewport>(sys::make_viewport(tilemap.size));

  add_ground_layers(m_registry, data);
  add_tile_objects(m_registry, m_tree, graphics, data, tileset);
  add_objects(m_registry, data);

  spawn_humanoids(tilemap, graphics);

  each<comp::depth_drawable, comp::humanoid>([&](comp::depth_drawable& drawable) {
    drawable.layer = tilemap.humanoidLayer;
  });

  sys::center_viewport_on(m_registry, player_spawnpoint());
  sys::update_drawable_movables(m_registry);
  m_tree.rebuild();

  sys::sort_drawables(m_registry);
}

level::level(const std::filesystem::path& path, graphics_context& graphics)
{
  std::ifstream stream{path, std::ios::binary};
  input_archive archive{stream};

  m_registry = sys::restore_registry(archive);
  archive(m_tree);
  archive(m_tilemap);
  archive(m_playerSpawnPosition);
}

void level::save(const std::filesystem::path& path) const
{
  std::ofstream stream{path, std::ios::binary};
  output_archive archive{stream};

  sys::save_registry(m_registry, archive);
  archive(m_tree);
  archive(m_tilemap);
  archive(m_playerSpawnPosition);
}

void level::relocate_aabb(const entt::entity entity, const float2& position)
{
  m_tree.relocate(entity, position);
}

void level::update_render_bounds()
{
  sys::update_render_bounds(m_registry, row_count(), col_count());
}

auto level::id() const noexcept -> map_id
{
  return m_registry.get<comp::tilemap>(m_tilemap).id;
}

auto level::get_aabb(const entt::entity id) const -> const level::aabb_type&
{
  return m_tree.get_aabb(id);
}

auto level::tilemap() const -> comp::tilemap::entity
{
  return m_tilemap;
}

auto level::player_spawnpoint() const -> const float2&
{
  return m_playerSpawnPosition.value();
}

auto level::row_count() const -> int
{
  return m_registry.get<comp::tilemap>(m_tilemap).rows;
}

auto level::col_count() const -> int
{
  return m_registry.get<comp::tilemap>(m_tilemap).cols;
}

auto level::registry() -> entt::registry&
{
  return m_registry;
}

auto level::registry() const -> const entt::registry&
{
  return m_registry;
}

void level::spawn_humanoids(const comp::tilemap& tilemap, graphics_context& graphics)
{
  // The player has to be created before other humanoids
  m_registry.set<ctx::player>(
      sys::add_player(m_registry, m_tree, *m_playerSpawnPosition, graphics));

  each<comp::spawnpoint>([&, this](const comp::spawnpoint& spawnpoint) {
    switch (spawnpoint.type)
    {
      case comp::spawnpoint_type::player:
        break;

      case comp::spawnpoint_type::skeleton: {
        sys::add_skeleton(m_registry, m_tree, spawnpoint.position, graphics);
        break;
      }
    }
  });
}

}  // namespace wanderer
