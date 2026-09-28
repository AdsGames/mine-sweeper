#include "./Menu.h"

#include <asw/asw.h>
#include <memory>

#include "../globals.h"
#include "../ui/ImageButton.h"

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

  const auto start = [this](int difficulty) {
    return [this, difficulty]() {
      game_difficulty = difficulty;
      manager.set_next_scene(States::Game);
    };
  };

  ui->root.add_child<ImageButton>("assets/images/buttons/start_easy.png",
                                  "assets/images/buttons/start_easy_hover.png",
                                  asw::Vec2<float>(25, 45), start(0));
  ui->root.add_child<ImageButton>(
      "assets/images/buttons/start_medium.png",
      "assets/images/buttons/start_medium_hover.png", asw::Vec2<float>(25, 60),
      start(1));
  ui->root.add_child<ImageButton>("assets/images/buttons/start_hard.png",
                                  "assets/images/buttons/start_hard_hover.png",
                                  asw::Vec2<float>(25, 75), start(2));
  ui->root.add_child<ImageButton>(
      "assets/images/buttons/quit.png", "assets/images/buttons/quit_hover.png",
      asw::Vec2<float>(25, 90), []() { asw::core::exit(); });
}

// Update game
void Menu::update(float dt) {
  Scene::update(dt);
  ui->update();

  if (asw::input::get_key_down(asw::input::Key::Escape)) {
    asw::core::exit();
  }
}

// Draw to screen
void Menu::draw() {
  Scene::draw();
  ui->draw();
}
