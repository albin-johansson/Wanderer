#pragma once

#include <array>    // array
#include <cstddef>  // byte

#include "core/aliases/ints.hpp"

namespace wanderer {

template <typename T, usize amount>
using buffer_t = std::array<std::byte, amount * sizeof(T)>;

}  // namespace wanderer
