#include "Menu.h"

#include "globals.h"
#include "utility/tools.h"
#include "utility/MouseListener.h"


Menu::Menu()
  : buffer (create_bitmap (128, 128)),
    title (load_png_ex ("images/title.png")),
    main_menu (load_png_ex ("images/main_menu.png")),
    start_easy (Button (25, 45)),
    start_medium (Button (25, 60)),
    start_hard (Button (25, 75)),
    quit (Button (25, 90))
{

  // Title
  set_window_title ("Minesweeper - A.D.S. Games");

  // Buttons
  start_easy.SetImages ("images/buttons/start_easy.png", "images/buttons/start_easy_hover.png");
  start_easy.SetOnClick ([this]() {
    game_difficulty = 0;
    set_next_state (STATE_GAME);
  });

  start_medium.SetImages ("images/buttons/start_medium.png", "images/buttons/start_medium_hover.png");
  start_medium.SetOnClick ([this]() {
    game_difficulty = 1;
    set_next_state (STATE_GAME);
  });

  start_hard.SetImages ("images/buttons/start_hard.png", "images/buttons/start_hard_hover.png");
  start_hard.SetOnClick ([this]() {
    game_difficulty = 2;
    set_next_state (STATE_GAME);
  });


  quit.SetImages ("images/buttons/quit.png", "images/buttons/quit_hover.png");
  quit.SetOnClick ([this]() {
    set_next_state (STATE_EXIT);
  });
}

// Destructor
Menu::~Menu() {
  highcolor_fade_out (8);

  // Destroy bitmaps
  destroy_bitmap (main_menu);
  destroy_bitmap (title);
  destroy_bitmap (buffer);
}

// Update game
void Menu::update() {
  start_easy.Update();
  start_medium.Update();
  start_hard.Update();
  quit.Update();

  if (key[KEY_ESC])
    set_next_state (STATE_EXIT);
}

// Draw to screen
void Menu::draw() {
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
