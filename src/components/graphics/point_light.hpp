#pragma once

#include "float2.hpp"

namespace wanderer::comp {

struct point_light final
{
  float2 position;         ///< The world position of the light.
  float size;              ///< Base size of the light.
  float fluctuation;       ///< Fluctuation size in [-fluctuationLimit, fluctuationLimit].
  float fluctuationStep;   ///< Size of each fluctuation increment.
  float fluctuationLimit;  ///< Fluctuation size limit.
};

}  // namespace wanderer::comp
