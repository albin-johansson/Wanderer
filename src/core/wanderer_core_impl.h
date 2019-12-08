#pragma once
#include "wanderer_core.h"
#include "viewport.h"
#include "image_generator.h"

#include "menu_state_machine.h"

namespace albinjohansson::wanderer {

class IMenuStateMachine;
class SoundEngine;
class IPlayer;
class ITileMap;

/**
 * The WandererCoreImpl class is an implementation of the IWandererCore interface.
 *
 * @since 0.1.0
 */
class WandererCoreImpl final : public IWandererCore {
 private:
  std::unique_ptr<IMenuStateMachine> menuStateMachine = nullptr;
  std::shared_ptr<SoundEngine> soundEngine = nullptr;
  std::shared_ptr<IPlayer> player = nullptr;
  std::shared_ptr<ITileMap> world = nullptr;
  std::shared_ptr<ITileMap> activeMap = nullptr;
  Viewport viewport;
  bool shouldQuit = false;

  explicit WandererCoreImpl(ImageGenerator& imageGenerator);

  void LoadSounds();

 public:
  ~WandererCoreImpl() override;

  /**
   * Creates and returns a unique pointer to an IWandererCore instance.
   *
   * @param imageGenerator a reference to an image generator.
   * @return a unique pointer to an IWandererCore instance.
   * @since 0.1.0
   */
  friend IWandererCore_uptr CreateCore(ImageGenerator& imageGenerator);

  void HandleInput(const Input& input) override;

  void Update(float delta) override;

  void Render(Renderer& renderer, float alpha) override;

  void SetMap(std::shared_ptr<ITileMap> map) override;

  void PlaySound(const std::string& id) const override;

  void Quit() noexcept override;

  void SetViewportWidth(float width) override;

  void SetViewportHeight(float height) override;

  [[nodiscard]] inline bool ShouldQuit() const noexcept override {
    return shouldQuit;
  }

  [[nodiscard]] const IPlayer& GetPlayer() const override {
    return *player;
  }
};

}
