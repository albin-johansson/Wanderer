#pragma once
#include <string>
#include <map>

namespace albinjohansson::tiled {

class TiledObject final {
 private:
  std::map<std::string, std::string> attributes;

 public:
  TiledObject();

  ~TiledObject();

  void AddAttribute(const std::string& id, const std::string& value);

  [[nodiscard]] const std::string& GetAttribute(const std::string& id) const;

  [[nodiscard]] bool HasAttribute(const std::string& id) const;
};

}