#include "Menu.h"

#include <asw/util/KeyListener.h>
#include <asw/util/MouseListener.h>

#include "globals.h"
#include "utility/tools.h"

void Menu::init() {
  title = asw::load::texture("assets/images/title.png");
  main_menu = asw::load::texture("assets/images/main_menu.png");
  start_easy = Button(25, 45);
  start_medium = Button(25, 60);
  start_hard = Button(25, 75);
  quit = Button(25, 90);

  // Title
  asw::display::setTitle("Minesweeper - A.D.S. Games");

  // Buttons
  start_easy.SetImages("assets/images/buttons/start_easy.png",
                       "assets/images/buttons/start_easy_hover.png");
  start_easy.SetOnClick([this]() {
    game_difficulty = 0;
    setNextState(StateEngine::STATE_GAME);
  });

  start_medium.SetImages("assets/images/buttons/start_medium.png",
                         "assets/images/buttons/start_medium_hover.png");
  start_medium.SetOnClick([this]() {
    game_difficulty = 1;
    setNextState(StateEngine::STATE_GAME);
  });

  start_hard.SetImages("assets/images/buttons/start_hard.png",
                       "assets/images/buttons/start_hard_hover.png");
  start_hard.SetOnClick([this]() {
    game_difficulty = 2;
    setNextState(StateEngine::STATE_GAME);
  });

  quit.SetImages("assets/images/buttons/quit.png",
                 "assets/images/buttons/quit_hover.png");
  quit.SetOnClick([this]() { setNextState(StateEngine::STATE_EXIT); });
}

// Update game
void Menu::update() {
  start_easy.Update();
  start_medium.Update();
  start_hard.Update();
  quit.Update();

  if (KeyListener::keyPressed[SDL_SCANCODE_ESCAPE]) {
    setNextState(StateEngine::STATE_EXIT);
  }
}

// Draw to screen
void Menu::draw() {
  // Draw menu
  asw::draw::sprite(title, 0, 0);
  asw::draw::sprite(main_menu, 14, 31);

  // Buttons
  start_easy.Draw();
  start_medium.Draw();
  start_hard.Draw();
  quit.Draw();
}
