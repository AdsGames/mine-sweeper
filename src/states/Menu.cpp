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
  ui = std::make_unique<asw::ui::Root>();
  ui->ctx.navigation = controls::navigation();
  ui->on_back = []() { asw::core::exit(); };

  // Image only buttons: the hover image shows focus, so hide the focus ring
  ui->ctx.theme.focus_ring.width = 0;

  const auto add_button = [this](const std::string& name,
                                 const asw::Vec2<float>& position,
                                 std::function<void()> on_click) {
    const std::string path = "assets/images/buttons/" + name;
    auto& button = ui->root.add_child<asw::ui::Button>();
    button.set_images(asw::assets::load_texture(path + ".png"),
                      asw::assets::load_texture(path + "_hover.png"));
    button.transform.position = position;
    button.on_click = std::move(on_click);
  };

  const auto start = [this](int difficulty) {
    return [this, difficulty]() {
      game_difficulty = difficulty;
      manager.set_next_scene(States::Game);
    };
  };

  add_button("start_easy", asw::Vec2<float>(25, 45), start(0));
  add_button("start_medium", asw::Vec2<float>(25, 60), start(1));
  add_button("start_hard", asw::Vec2<float>(25, 75), start(2));
  add_button("quit", asw::Vec2<float>(25, 90), []() { asw::core::exit(); });
}

// Update game
void Menu::update(float dt) {
  Scene::update(dt);
  ui->update();
}

// Draw to screen
void Menu::draw() {
  Scene::draw();
  ui->draw();
}
