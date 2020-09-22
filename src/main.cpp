#ifdef NDEBUG
#define BOOST_DISABLE_ASSERTS
#endif

#include <centurion.hpp>
#include <font.hpp>
#include <hints.hpp>
#include <log.hpp>
#include <surface.hpp>

#include "application.h"
#include "random_utils.h"

using namespace wanderer;

int main(int, char**)
{
  math::init_rnd();
  cen::library lib;

  using cen::hint::render_driver;
  cen::set_hint<render_driver>(render_driver::value::opengl);
  cen::log::set_priority(cen::log::priority::info);

  application app;
  app.run();
  return 0;
}