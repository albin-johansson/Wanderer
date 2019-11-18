#include "entity_idle_delegate.h"
#include "objects.h"
#include "entity_sheet.h"
#include "entity_draw_delegate.h"

namespace wanderer::core {

EntityIdleDelegate::EntityIdleDelegate(IEntity* entity, IEntityStateMachine* parent) {
  this->entity = Objects::RequireNonNull(entity);
  this->parent = Objects::RequireNonNull(parent);
}

EntityIdleDelegate::~EntityIdleDelegate() = default;

void EntityIdleDelegate::Draw(visuals::Renderer& renderer, const Viewport& viewport) {
  float srcY = EntitySheet::GetSourceY(512, entity->GetDominantDirection());
  EntityDrawDelegate::Draw(renderer, viewport, *entity, 0, srcY);
}

void EntityIdleDelegate::Enter() {}

void EntityIdleDelegate::Exit() {}

void EntityIdleDelegate::Tick(float delta) {}

}