#include "directories.hpp"

#include <centurion.hpp>  // preferred_path

namespace wanderer {

auto files_directory() -> const std::filesystem::path&
{
  static std::filesystem::path path =
      cen::preferred_path("albin-johansson", "wanderer").copy();
  return path;
}

auto saves_directory() -> const std::filesystem::path&
{
  static auto path = files_directory() / "saves";
  return path;
}

}  // namespace wanderer