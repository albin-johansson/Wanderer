#include <SDL.h>
#include <string>

namespace wanderer::view {

/**
 * The Window class is a wrapper around an SDL_Window instance.
 *
 * @since 0.1.0
 */
class Window final {
 private:
  SDL_Window* window = nullptr;

 public:
  /**
   * Creates a window instance. The window will be hidden by default.
   *
   * @param width the width of the window, must be greater than zero.
   * @param height the height of the window, must be greater than zero.
   * @throws invalid_argument if the supplied width or height values aren't
   * greater than zero.
   * @since 0.1.0
   */
  Window(const std::string& title, int width, int height);

  ~Window();

  /**
   * Makes the window visible.
   *
   * @since 0.1.0
   */
  void Show() noexcept;

  /**
   * Makes the window invisible.
   *
   * @since 0.1.0
   */
  void Hide() noexcept;

  /**
   * Sets whether or not the window is in fullscreen mode.
   *
   * @param isFullscreen true if the window should enable fullscreen mode; false
   * otherwise.
   * @since 0.1.0
   */
  void SetFullscreen(bool isFullscreen) noexcept;

  /**
   * Sets whether or not the window should be resizable.
   *
   * @param isResizable true if the window should be resizable; false otherwise.
   * @since 0.1.0
   */
  void SetResizable(bool isResizable) noexcept;

  /**
   * Sets the width of the window.
   *
   * @param width the new width of the window.
   * @throws invalid_argument if the supplied width isn't greater than zero.
   * @since 0.1.0
   */
  void SetWidth(int width);

  /**
   * Sets the height of the window.
   *
   * @param height the new height of the window.
   * @throws invalid_argument if the supplied height isn't greater than
   * zero.
   * @since 0.1.0
   */
  void SetHeight(int height);

  /**
   * Indicates whether or not the window is resizable.
   *
   * @return true if the window is resizable; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool IsResizable() const noexcept;

  /**
   * Indicates whether or not the window is in fullscreen mode.
   *
   * @return true if the window is in fullscreen mode; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool IsFullscreen() const noexcept;

  /**
   * Indicates whether or not the window is visible.
   *
   * @return true if the window is visible; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool IsVisible() const noexcept;

  /**
   * Returns the current width of the window.
   *
   * @return the current width of the window.
   * @since 0.1.0
   */
  [[nodiscard]] int GetWidth() const noexcept;

  /**
   * Returns the current height of the window.
   *
   * @return the current height of the window.
   * @since 0.1.0
   */
  [[nodiscard]] int GetHeight() const noexcept;

  /**
   * Returns the internal representation of the window. Do not free
   * the SDL_Window referenced by the returned pointer!
   *
   * @return the internal representation of the window.
   * @since 0.1.0
   */
  [[nodiscard]] inline SDL_Window* GetInternalWindow() noexcept {
    return window;
  }
};

}  // namespace wanderer::view