#include "menu.h"

#include <loadpng.h>

#include "globals.h"
#include "tools.h"
#include "mouseListener.h"

menu::menu() {
  // Creates a buffer
  buffer = create_bitmap(128, 128);

  // Load menu background
  title = load_png("images/title.png", NULL);

  // Load menu
  main_menu = load_png("images/main_menu.png", NULL);

  // Buttons
  start_easy = Button(25, 45);
  start_easy.setImages("images/buttons/start_easy.png", "images/buttons/start_easy_hover.png");

  start_medium = Button(25, 60);
  start_medium.setImages("images/buttons/start_medium.png", "images/buttons/start_medium_hover.png");

  start_hard = Button(25, 75);
  start_hard.setImages("images/buttons/start_hard.png", "images/buttons/start_hard_hover.png");

  quit = Button(25, 90);
  quit.setImages("images/buttons/quit.png", "images/buttons/quit_hover.png");


  // Cursor
  enable_hardware_cursor();
  select_mouse_cursor(MOUSE_CURSOR_ARROW);
  show_mouse(screen);
}

// Destructor
menu::~menu() {
  highcolor_fade_out(8);

  // Destroy bitmaps
  destroy_bitmap(main_menu);
  destroy_bitmap(title);
  destroy_bitmap(buffer);
}

// Update game
void menu::update() {
  // Button presses
  if (mouseListener::buttonPressed[1]) {
    if (start_easy.hovering()) {
      game_difficulty = 4;
      set_next_state(STATE_GAME);
    }
    else if (start_medium.hovering()) {
      game_difficulty = 8;
      set_next_state(STATE_GAME);
    }
    else if (start_hard.hovering()) {
      game_difficulty = 16;
      set_next_state(STATE_GAME);
    }
    else if (quit.hovering()) {
      set_next_state(STATE_EXIT);
    }
  }
}

// Draw to screen
void menu::draw() {
  // Draw menu
  draw_sprite(buffer, title, 0, 0);
  draw_sprite(buffer, main_menu, 14, 31);

  // Buttons
  start_easy.draw(buffer);
  start_medium.draw(buffer);
  start_hard.draw(buffer);
  quit.draw(buffer);

  // Buffer to screen
  stretch_sprite(screen, buffer, 0, 0, SCREEN_W, SCREEN_H);
}
