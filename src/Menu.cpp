#include "Menu.h"

#include "globals.h"
#include "utility/KeyListener.h"
#include "utility/MouseListener.h"
#include "utility/tools.h"

void Menu::init() {
  title = aar::load::bitmap("assets/images/title.png");
  main_menu = aar::load::bitmap("assets/images/main_menu.png");
  start_easy = Button(25, 45);
  start_medium = Button(25, 60);
  start_hard = Button(25, 75);
  quit = Button(25, 90);

  // Title
  aar::display::setTitle("Minesweeper - A.D.S. Games");

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

// Destructor
void Menu::cleanup() {
  // Destroy bitmaps
  aar::load::destroyTexture(main_menu);
  aar::load::destroyTexture(title);
}

// Update game
void Menu::update() {
  start_easy.Update();
  start_medium.Update();
  start_hard.Update();
  quit.Update();

  if (KeyListener::keyDown[SDL_SCANCODE_ESCAPE]) {
    setNextState(StateEngine::STATE_EXIT);
  }
}

// Draw to screen
void Menu::draw() {
  // Draw menu
  aar::draw::sprite(title, 0, 0);
  aar::draw::sprite(main_menu, 14, 31);

  // Buttons
  start_easy.Draw();
  start_medium.Draw();
  start_hard.Draw();
  quit.Draw();
}
