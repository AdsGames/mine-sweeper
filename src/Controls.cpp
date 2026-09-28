#include "Controls.h"

namespace {
using asw::input::ControllerButton;
using asw::input::ControllerButtonBinding;
using asw::input::MouseButton;
using asw::input::MouseButtonBinding;

constexpr auto ANY = asw::input::ANY_CONTROLLER;

asw::ui::Navigation ui_navigation;
}  // namespace

void controls::bind() {
  // Arrows, Tab, Return, Space, Escape, D-pad, left stick, shoulders, A and B
  ui_navigation = asw::ui::bind_default_navigation();

  // Start also confirms and Back also goes back, as before
  asw::input::bind_action(ui_navigation.activate,
                          ControllerButtonBinding{ControllerButton::Start, ANY});
  asw::input::bind_action(ui_navigation.back,
                          ControllerButtonBinding{ControllerButton::Back, ANY});

  asw::input::bind_action(REVEAL, MouseButtonBinding{MouseButton::Left});
  asw::input::bind_action(FLAG, MouseButtonBinding{MouseButton::Right});
}

const asw::ui::Navigation& controls::navigation() {
  return ui_navigation;
}
