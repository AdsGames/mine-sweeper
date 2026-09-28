#include "Controls.h"

#include <array>

namespace {
using asw::input::ControllerAxis;
using asw::input::ControllerAxisBinding;
using asw::input::ControllerButton;
using asw::input::ControllerButtonBinding;
using asw::input::Key;
using asw::input::KeyBinding;
using asw::input::MouseButton;
using asw::input::MouseButtonBinding;

constexpr auto ANY = asw::input::ANY_CONTROLLER;

// Stick must pass this before it counts as a direction
constexpr float STICK_THRESHOLD = 0.5F;

void bind_direction(const char* name,
                    ControllerButton dpad,
                    ControllerAxis axis,
                    bool positive) {
  asw::input::bind_action(name, ControllerButtonBinding{dpad, ANY});
  asw::input::bind_action(
      name, ControllerAxisBinding{axis, ANY, STICK_THRESHOLD, positive});
}

struct Direction {
  const char* action;
  int dx;
  int dy;
};

constexpr std::array<Direction, 4> DIRECTIONS = {{
    {controls::UI_UP, 0, -1},
    {controls::UI_DOWN, 0, 1},
    {controls::UI_LEFT, -1, 0},
    {controls::UI_RIGHT, 1, 0},
}};
}  // namespace

void controls::bind() {
  // Arrow keys and Return are handled by the asw ui root, so the ui
  // directions and confirm are controller only
  bind_direction(UI_UP, ControllerButton::DPadUp, ControllerAxis::LeftY,
                 false);
  bind_direction(UI_DOWN, ControllerButton::DPadDown, ControllerAxis::LeftY,
                 true);
  bind_direction(UI_LEFT, ControllerButton::DPadLeft, ControllerAxis::LeftX,
                 false);
  bind_direction(UI_RIGHT, ControllerButton::DPadRight, ControllerAxis::LeftX,
                 true);

  asw::input::bind_action(UI_CONFIRM,
                          ControllerButtonBinding{ControllerButton::A, ANY});
  asw::input::bind_action(
      UI_CONFIRM, ControllerButtonBinding{ControllerButton::Start, ANY});

  asw::input::bind_action(UI_BACK, KeyBinding{Key::Escape});
  asw::input::bind_action(UI_BACK,
                          ControllerButtonBinding{ControllerButton::Back, ANY});

  asw::input::bind_action(REVEAL, MouseButtonBinding{MouseButton::Left});
  asw::input::bind_action(FLAG, MouseButtonBinding{MouseButton::Right});
}

void controls::update_ui(asw::ui::Root& ui) {
  ui.update();

  auto& ctx = ui.ctx;

  for (const auto& direction : DIRECTIONS) {
    if (asw::input::get_action_down(direction.action)) {
      ctx.focus.focus_dir(ctx, direction.dx, direction.dy);
      ctx.theme.show_focus = true;
    }
  }

  if (asw::input::get_action_down(UI_CONFIRM)) {
    ui.dispatch_to_focused(
        asw::ui::UIEvent{.type = asw::ui::UIEvent::Type::Activate});
  }
}
