#pragma once
#include <memory>

namespace wanderer::controller {

/**
 * The IWandererController interface specifies the facade for the main controller of the Wanderer
 * application.
 *
 * @since 0.1.0
 */
class IWandererController {
 protected:
  IWandererController() = default;

 public:
  virtual ~IWandererController() = default;

  /**
   * Runs the application.
   *
   * @since 0.1.0
   */
  virtual void Run() = 0;

  /**
   * Quits the application.
   *
   * @since 0.1.0
   */
  virtual void Quit() = 0;
};

using IWandererController_uptr = std::unique_ptr<IWandererController>;

}