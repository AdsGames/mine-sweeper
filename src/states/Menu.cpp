#include "./Menu.h"

#include <asw/asw.h>
#include <memory>

#include "../globals.h"

void Menu::init() {
  // Title
  auto title = std::make_shared<asw::game::Sprite>();
  title->transform.position = asw::Vec2<float>(0, 0);
  title->setTexture(asw::assets::loadTexture("assets/images/title.png"));
  registerObject(title);

  // Main menu
  auto main_menu = std::make_shared<asw::game::Sprite>();
  main_menu->transform.position = asw::Vec2<float>(14, 31);
  main_menu->setTexture(
      asw::assets::loadTexture("assets/images/main_menu.png"));
  registerObject(main_menu);

  // Buttons
  auto start_easy = std::make_shared<Button>();
  start_easy->transform.position = asw::Vec2<float>(25, 45);
  start_easy->setImages("assets/images/buttons/start_easy.png",
                        "assets/images/buttons/start_easy_hover.png");
  start_easy->setOnClick([this]() {
    game_difficulty = 0;
    this->sceneManager.setNextScene(States::Game);
  });
  registerObject(start_easy);

  auto start_medium = std::make_shared<Button>();
  start_medium->transform.position = asw::Vec2<float>(25, 60);
  start_medium->setImages("assets/images/buttons/start_medium.png",
                          "assets/images/buttons/start_medium_hover.png");
  start_medium->setOnClick([this]() {
    game_difficulty = 1;
    sceneManager.setNextScene(States::Game);
  });
  registerObject(start_medium);

  auto start_hard = std::make_shared<Button>();
  start_hard->transform.position = asw::Vec2<float>(25, 75);
  start_hard->setImages("assets/images/buttons/start_hard.png",
                        "assets/images/buttons/start_hard_hover.png");
  start_hard->setOnClick([this]() {
    game_difficulty = 2;
    sceneManager.setNextScene(States::Game);
  });
  registerObject(start_hard);

  auto quit = std::make_shared<Button>();
  quit->transform.position = asw::Vec2<float>(25, 90);
  quit->setImages("assets/images/buttons/quit.png",
                  "assets/images/buttons/quit_hover.png");
  quit->setOnClick([]() { asw::core::exit = true; });
  registerObject(quit);
}

// Update game
void Menu::update(float deltaTime) {
  Scene::update(deltaTime);

  if (asw::input::wasKeyPressed(asw::input::Key::ESCAPE)) {
    asw::core::exit = true;
  }
}

// Draw to screen
void Menu::draw() {
  Scene::draw();
}
