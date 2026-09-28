#pragma once

#include <asw/asw.h>

// Input actions shared by mouse, keyboard and controllers
namespace controls {

// Menu and screen actions, any controller
inline constexpr const char* UI_UP = "ui_up";
inline constexpr const char* UI_DOWN = "ui_down";
inline constexpr const char* UI_LEFT = "ui_left";
inline constexpr const char* UI_RIGHT = "ui_right";
inline constexpr const char* UI_CONFIRM = "ui_confirm";
inline constexpr const char* UI_BACK = "ui_back";

// Minefield actions
inline constexpr const char* REVEAL = "reveal";
inline constexpr const char* FLAG = "flag";

// Bind all actions, call once after asw::core::init
void bind();

// Update a ui root, and move focus or activate buttons with a controller.
// The root already handles the mouse and keyboard.
void update_ui(asw::ui::Root& ui);

}  // namespace controls
