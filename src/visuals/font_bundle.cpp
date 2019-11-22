#include "font_bundle.h"

namespace wanderer::visuals {

FontBundle::FontBundle(const std::string& file)
    : font12(file, 12),
      font16(file, 16),
      font24(file, 24),
      font36(file, 36) {}

FontBundle::~FontBundle() = default;

FontBundle_uptr FontBundle::Create(const std::string& file) {
  return std::make_unique<FontBundle>(file);
}

}
