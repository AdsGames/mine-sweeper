#include "./Menu.h"

#include <asw/asw.h>
#include <functional>
#include <memory>
#include <string>
#include <utility>

#include "../Controls.h"
#include "../globals.h"

void Menu::init() {
  // Title
  auto title = create_object<asw::game::Sprite>();
  title->transform.position = asw::Vec2<float>(0, 0);
  title->set_texture(asw::assets::load_texture("assets/images/title.png"));

  // Main menu
  auto main_menu = create_object<asw::game::Sprite>();
  main_menu->transform.position = asw::Vec2<float>(14, 31);
  main_menu->set_texture(
      asw::assets::load_texture("assets/images/main_menu.png"));

  // Buttons
  const auto screen_size = asw::display::get_logical_size();
  ui = std::make_unique<asw::ui::Root>();
  ui->set_size(screen_size.x, screen_size.y);

  // Image only buttons: the hover image also shows while focused, so hide the
  // theme focus ring
  ui->ctx.theme.btn_focus_ring = asw::Color{0, 0, 0, 0};

  const auto add_button = [this](const std::string& image,
                                 const std::string& hover_image,
                                 const asw::Vec2<float>& position,
                                 std::function<void()> on_click) {
    auto& button = ui->root.add_child<asw::ui::Button>();
    button.draw_background = false;
    button.set_texture(asw::assets::load_texture(image), true);
    button.texture_hover = asw::assets::load_texture(hover_image);
    button.transform.position = position;
    button.on_click = std::move(on_click);
  };

  const auto start = [this](int difficulty) {
    return [this, difficulty]() {
      game_difficulty = difficulty;
      manager.set_next_scene(States::Game);
    };
  };

  add_button("assets/images/buttons/start_easy.png",
             "assets/images/buttons/start_easy_hover.png",
             asw::Vec2<float>(25, 45), start(0));
  add_button("assets/images/buttons/start_medium.png",
             "assets/images/buttons/start_medium_hover.png",
             asw::Vec2<float>(25, 60), start(1));
  add_button("assets/images/buttons/start_hard.png",
             "assets/images/buttons/start_hard_hover.png",
             asw::Vec2<float>(25, 75), start(2));
  add_button("assets/images/buttons/quit.png",
             "assets/images/buttons/quit_hover.png", asw::Vec2<float>(25, 90),
             []() { asw::core::exit(); });
}

// Update game
void Menu::update(float dt) {
  Scene::update(dt);
  controls::update_ui(*ui);

  if (asw::input::get_action_down(controls::UI_BACK)) {
    asw::core::exit();
  }
}

// Draw to screen
void Menu::draw() {
  Scene::draw();
  ui->draw();
}
