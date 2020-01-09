#pragma once
#include <memory>
#include "abstract_entity.h"
#include "entity_state_machine.h"
#include "tile.h"
#include "game_constants.h"

namespace albinjohansson::wanderer {

class Skeleton final : public AbstractEntity {
 private:
  std::unique_ptr<IEntityStateMachine> stateMachine = nullptr;

  void init();

 public:
  static constexpr float HOMING_RANGE = GameConstants::tile_size * 4.0f;

  explicit Skeleton(const std::shared_ptr<centurion::Image>& sheet);

  ~Skeleton() override;

  void tick(IWandererCore& core, float delta) override;

  void draw(const centurion::Renderer& renderer, const Viewport& viewport) const override;

};

}
