#pragma once

#include "core/aliases/entity_type.hpp"
#include "core/aliases/ints.hpp"

namespace wanderer::comp {

namespace tags {
struct object_tag;
}  // namespace tags

struct object final
{
  using entity = entity_type<tags::object_tag>;

  int id{};
};

void serialize(auto& archive, object& o, uint32 version)
{
  archive(o.id);
}

}  // namespace wanderer::comp
