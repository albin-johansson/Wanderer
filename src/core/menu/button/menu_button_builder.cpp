#include "menu_button_builder.h"

#include "json_utils.h"

using namespace centurion;

namespace albinjohansson::wanderer {

UniquePtr<MenuButton> MenuButtonBuilder::build(ActionParser& actionParser,
                                               const JsonValue& json,
                                               int row)
{
  auto text = maybe_get<std::string>(json, "text");
  if (!text) {
    return nullptr;
  }

  auto action = actionParser.parse(json, "action");
  if (!action) {
    return nullptr;
  }

  const auto x = 200.0f;
  const auto y = 200.0f + static_cast<float>(row * 70);

  return std::make_unique<MenuButton>(
      *text, FRect{x, y, 200, 50}, std::move(action));
}

}  // namespace albinjohansson::wanderer
