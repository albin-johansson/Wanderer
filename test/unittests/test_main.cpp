#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "centurion.h"

int main(int argc, char** argv) {
  using namespace centurion;
  Centurion c;
  return Catch::Session().run(argc, argv);
}