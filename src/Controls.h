#pragma once

#include <asw/asw.h>

// Input actions shared by mouse, keyboard and controllers
namespace controls {

// Menu and screen actions, keyboard and any controller. The names match the
// ones asw::ui::bind_default_navigation gives.
inline constexpr const char* UI_CONFIRM = "ui_activate";
inline constexpr const char* UI_BACK = "ui_back";

// Minefield actions
inline constexpr const char* REVEAL = "reveal";
inline constexpr const char* FLAG = "flag";

// Bind all actions, call once after asw::core::init
void bind();

// Ui navigation actions, set on asw::ui::Root::ctx.navigation
const asw::ui::Navigation& navigation();

}  // namespace controls
