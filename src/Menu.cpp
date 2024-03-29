#include "Menu.h"

#include <asw/asw.h>

#include "globals.h"
#include "utility/tools.h"

void Menu::init() {
  title = asw::assets::loadTexture("assets/images/title.png");
  main_menu = asw::assets::loadTexture("assets/images/main_menu.png");
  start_easy = Button(25, 45);
  start_medium = Button(25, 60);
  start_hard = Button(25, 75);
  quit = Button(25, 90);

  // Title
  asw::display::setTitle("Minesweeper - A.D.S. Games");

  // Buttons
  start_easy.setImages("assets/images/buttons/start_easy.png",
                       "assets/images/buttons/start_easy_hover.png");
  start_easy.setOnClick([this]() {
    game_difficulty = 0;
    setNextState(ProgramState::STATE_GAME);
  });

  start_medium.setImages("assets/images/buttons/start_medium.png",
                         "assets/images/buttons/start_medium_hover.png");
  start_medium.setOnClick([this]() {
    game_difficulty = 1;
    setNextState(ProgramState::STATE_GAME);
  });

  start_hard.setImages("assets/images/buttons/start_hard.png",
                       "assets/images/buttons/start_hard_hover.png");
  start_hard.setOnClick([this]() {
    game_difficulty = 2;
    setNextState(ProgramState::STATE_GAME);
  });

  quit.setImages("assets/images/buttons/quit.png",
                 "assets/images/buttons/quit_hover.png");
  quit.setOnClick([this]() { setNextState(ProgramState::STATE_EXIT); });
}

// Update game
void Menu::update() {
  start_easy.update();
  start_medium.update();
  start_hard.update();
  quit.update();

  if (asw::input::keyboard.pressed[SDL_SCANCODE_ESCAPE]) {
    setNextState(ProgramState::STATE_EXIT);
  }
}

// Draw to screen
void Menu::draw() {
  // Draw menu
  asw::draw::sprite(title, 0, 0);
  asw::draw::sprite(main_menu, 14, 31);

  // Buttons
  start_easy.draw();
  start_medium.draw();
  start_hard.draw();
  quit.draw();
}
