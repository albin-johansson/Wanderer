#pragma once
#include <pugixml.hpp>
#include <string>

namespace wanderer {

class PugiUtils final {
 public:
  PugiUtils() = delete;

  ~PugiUtils() = default;

  [[nodiscard]] static pugi::xml_document LoadDocument(const std::string& path);
};

}  // namespace wanderer
