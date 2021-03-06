#pragma once

#include "entity_type.hpp"
#include "ints.hpp"

namespace wanderer::comp {
namespace detail {
struct object_entity_t;
}

struct object final
{
  using entity = entity_type<detail::object_entity_t>;
  int id;
};

template <typename Archive>
void serialize(Archive& archive, object& o, u32 version)
{
  archive(o.id);
}

}  // namespace wanderer::comp
