#include "hud.h"

#include "game_constants.h"
#include "player.h"
#include "wanderer_core.h"

using namespace centurion;

namespace wanderer {

HUD::HUD() = default;

HUD::~HUD() = default;

void HUD::draw_health_bar(Renderer& renderer, IWandererCore& core) const
{
  const auto& player = core.get_player();

  const auto hp = player.get_health();
  const auto hpBarWidth = (hp / GameConstants::player_max_health) * 100;
  const auto hpBarHeight = 20;

  renderer.set_color(color::red);
  renderer.fill_rect({10, 720 - hpBarHeight - 10, hpBarWidth, hpBarHeight});

  renderer.set_color({0xAA, 0xFE, 0, 0xAA});
  renderer.fill_rect(
      {10, 720 - hpBarHeight - 10, hpBarWidth - 100, hpBarHeight});

  renderer.set_color(color::black);
  renderer.draw_rect({10, 720 - hpBarHeight - 10, hpBarWidth, hpBarHeight});
}

void HUD::draw(Renderer& renderer, IWandererCore& core) const
{
  draw_health_bar(renderer, core);
}

}  // namespace wanderer