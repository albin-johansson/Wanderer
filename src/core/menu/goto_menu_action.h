#pragma once
#include "action.h"
#include "menu_id.h"
#include "menu_state_machine.h"
#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

class GotoMenuAction final : public IAction {
 public:
  GotoMenuAction(weak<IMenuStateMachine> menuStateMachine,
                 MenuID menu) noexcept;

  ~GotoMenuAction() noexcept override = default;

  void execute() noexcept override;

 private:
  weak<IMenuStateMachine> m_menuStateMachine;
  MenuID m_menu;
};

}  // namespace albinjohansson::wanderer
