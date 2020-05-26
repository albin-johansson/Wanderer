#include "game_loop.h"

#include <screen.h>
#include <timer.h>

using namespace centurion;

namespace wanderer {

GameLoop::GameLoop() noexcept
{
  m_vsyncRate = static_cast<float>(Screen::refresh_rate());
  m_timeStep = 1.0f / m_vsyncRate;
  m_counterFreq = static_cast<float>(Timer::high_res_freq());
  m_now = Timer::high_res();
  m_then = m_now;
}

void GameLoop::smooth_delta() noexcept
{
  /* Reference for delta smoothing: https://frankforce.com/?p=2636 */

  m_delta += m_deltaBuffer;

  int frameCount = static_cast<int>(m_delta * m_vsyncRate + 1);
  if (frameCount <= 0) {
    frameCount = 1;
  }

  const float oldDelta = m_delta;
  m_delta = static_cast<float>(frameCount) / m_vsyncRate;
  m_deltaBuffer = oldDelta - m_delta;
}

void GameLoop::update(Game& game)
{
  m_then = m_now;
  m_now = Timer::high_res();

  m_delta = static_cast<float>(m_now - m_then) / m_counterFreq;

  if (m_delta > maxFrameTime) {
    m_delta = maxFrameTime;
  }

  smooth_delta();

  m_accumulator += m_delta;

  while (m_accumulator >= m_timeStep) {
    m_accumulator -= m_timeStep;
    game.tick(m_timeStep);
  }
}

}  // namespace wanderer
