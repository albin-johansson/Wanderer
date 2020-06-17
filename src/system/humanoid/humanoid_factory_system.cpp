#include "humanoid_factory_system.h"

#include <texture.h>
#include <timer.h>

#include <cassert>

#include "animated.h"
#include "binds.h"
#include "collision.h"
#include "depth_drawable.h"
#include "direction.h"
#include "game_constants.h"
#include "image_loader.h"
#include "movable.h"
#include "player.h"

using centurion::Renderer;
using centurion::Texture;
using centurion::Timer;

namespace wanderer::system::humanoid {
namespace {

/**
 * Adds a humanoid entity to the registry and returns the associated
 * identifier. The entity will have <code>Movable</code>,
 * <code>DepthDrawable</code>, <code>Animated</code>, <code>Collision</code>,
 * <code>Humanoid</code> and <code>HumanoidIdle</code> components added to it
 * . Select components will have default values assigned to them, which might
 * have to be tweaked for the specific humanoid.
 *
 * @pre <code>texture</code> must be a valid handle.
 * @param registry the registry that will be used.
 * @param texture the handle to the texture that will be used by the humanoid.
 * @return the identifier associated with the created humanoid.
 */
[[nodiscard]] entt::entity create_basic_humanoid(
    entt::registry& registry,
    const entt::handle<Texture>& texture)
{
  assert(texture);  // require valid handle

  const auto entity = registry.create();

  auto& movable = registry.emplace<Movable>(entity);
  movable.dominantDirection = Direction::Down;

  auto& drawable = registry.emplace<DepthDrawable>(entity);
  drawable.texture = texture;
  drawable.depth = 5;

  auto& animated = registry.emplace<Animated>(entity);
  animated.frame = 0;
  animated.delay = 65;
  animated.then = Timer::millis();
  animated.nFrames = 1;

  registry.emplace<Collision>(entity);
  registry.emplace<Humanoid>(entity);
  registry.emplace<HumanoidIdle>(entity);

  return entity;
}

}  // namespace

entt::entity add_player(entt::registry& registry,
                        Renderer& renderer,
                        ImageCache& imageCache)
{
  constexpr auto id = "player"_hs;
  if (!imageCache.contains(id)) {
    imageCache.load<ImageLoader>(id, renderer, "resource/img/player2.png");
  }

  const auto playerEntity =
      create_basic_humanoid(registry, imageCache.handle(id));

  registry.emplace<Player>(playerEntity);

  auto& movable = registry.get<Movable>(playerEntity);
  movable.speed = g_playerSpeed;
  movable.currentPos.x = 100;
  movable.currentPos.y = 100;
  movable.dominantDirection = Direction::Down;
  movable.oldPos = movable.currentPos;

  registry.emplace<Binds>(playerEntity);

  return playerEntity;
}

entt::entity add_skeleton(entt::registry& registry,
                          Renderer& renderer,
                          ImageCache& imageCache)
{
  constexpr auto id = "skeleton"_hs;
  if (!imageCache.contains(id)) {
    imageCache.load<ImageLoader>(id, renderer, "resource/img/skeleton.png");
  }

  const auto skeletonEntity =
      create_basic_humanoid(registry, imageCache.handle(id));

  auto& movable = registry.get<Movable>(skeletonEntity);
  movable.speed = g_monsterSpeed;
  movable.currentPos.x = 300;
  movable.currentPos.y = 300;
  movable.oldPos = movable.currentPos;

  auto& drawable = registry.get<DepthDrawable>(skeletonEntity);
  drawable.depth = 7;

  return skeletonEntity;
}

}  // namespace wanderer::system::humanoid
