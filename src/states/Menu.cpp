#include "./Menu.h"

#include <asw/asw.h>
#include <memory>

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
  auto start_easy = create_object<Button>();
  start_easy->transform.position = asw::Vec2<float>(25, 45);
  start_easy->setImages("assets/images/buttons/start_easy.png",
                        "assets/images/buttons/start_easy_hover.png");
  start_easy->setOnClick([this]() {
    game_difficulty = 0;
    this->manager.set_next_scene(States::Game);
  });

  auto start_medium = create_object<Button>();
  start_medium->transform.position = asw::Vec2<float>(25, 60);
  start_medium->setImages("assets/images/buttons/start_medium.png",
                          "assets/images/buttons/start_medium_hover.png");
  start_medium->setOnClick([this]() {
    game_difficulty = 1;
    manager.set_next_scene(States::Game);
  });

  auto start_hard = create_object<Button>();
  start_hard->transform.position = asw::Vec2<float>(25, 75);
  start_hard->setImages("assets/images/buttons/start_hard.png",
                        "assets/images/buttons/start_hard_hover.png");
  start_hard->setOnClick([this]() {
    game_difficulty = 2;
    manager.set_next_scene(States::Game);
  });

  auto quit = create_object<Button>();
  quit->transform.position = asw::Vec2<float>(25, 90);
  quit->setImages("assets/images/buttons/quit.png",
                  "assets/images/buttons/quit_hover.png");
  quit->setOnClick([]() { asw::core::exit(); });
}

// Update game
void Menu::update(float dt) {
  Scene::update(dt);

  if (asw::input::get_key_down(asw::input::Key::Escape)) {
    asw::core::exit();
  }
}

// Draw to screen
void Menu::draw() {
  Scene::draw();
}
