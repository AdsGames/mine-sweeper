#include "menu.h"

#include "globals.h"
#include "tools.h"
#include "mouseListener.h"


menu::menu() {
  // Creates a buffer
  buffer = create_bitmap (128, 128);

  // Load menu background
  title = load_png_ex ("images/title.png");

  // Load menu
  main_menu = load_png_ex ("images/main_menu.png");

  // Buttons
  start_easy = Button (25, 45);
  start_easy.SetImages ("images/buttons/start_easy.png", "images/buttons/start_easy_hover.png");
  start_easy.SetOnClick([this]() {
    game_difficulty = 4;
    set_next_state (STATE_GAME);
  });

  start_medium = Button (25, 60);
  start_medium.SetImages ("images/buttons/start_medium.png", "images/buttons/start_medium_hover.png");
  start_medium.SetOnClick([this]() {
    game_difficulty = 8;
    set_next_state (STATE_GAME);
  });

  start_hard = Button (25, 75);
  start_hard.SetImages ("images/buttons/start_hard.png", "images/buttons/start_hard_hover.png");
  start_hard.SetOnClick([this]() {
    game_difficulty = 16;
    set_next_state (STATE_GAME);
  });

  quit = Button (25, 90);
  quit.SetImages ("images/buttons/quit.png", "images/buttons/quit_hover.png");
  quit.SetOnClick([this]() {
    set_next_state (STATE_EXIT);
  });
}

// Destructor
menu::~menu() {
  highcolor_fade_out (8);

  // Destroy bitmaps
  destroy_bitmap (main_menu);
  destroy_bitmap (title);
  destroy_bitmap (buffer);
}

// Update game
void menu::update() {
  start_easy.Update();
  start_medium.Update();
  start_hard.Update();
  quit.Update();
}

// Draw to screen
void menu::draw() {
  // Draw menu
  draw_sprite (buffer, title, 0, 0);
  draw_sprite (buffer, main_menu, 14, 31);

  // Buttons
  start_easy.Draw (buffer);
  start_medium.Draw (buffer);
  start_hard.Draw (buffer);
  quit.Draw (buffer);

  // Buffer to screen
  stretch_sprite (screen, buffer, 0, 0, SCREEN_W, SCREEN_H);
}
