#include <gtest/gtest.h>

#include <centurion.hpp>

int main(int argc, char** argv)
{
  cen::library lib;
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
