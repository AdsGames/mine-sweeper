#include "menu.h"

menu::menu(){
  // Creates a buffer
  buffer = create_bitmap( 640, 640);

  // Load menu background
  main_menu = load_bitmap( "images/main_menu.png", NULL);

  // Buttons
  start_easy.SetImages( "images/buttons/start_easy", "images/buttons/start_easy_hover");
  start_medium.SetImages( "images/buttons/start_medium", "images/buttons/start_medium_hover");
  start_hard.SetImages( "images/buttons/start_hard", "images/buttons/start_hard_hover");
  quit.SetImages( "images/buttons/quit", "images/buttons/quit_hover");

  // Cursor
  enable_hardware_cursor();
  select_mouse_cursor(MOUSE_CURSOR_ARROW);
  show_mouse( screen);
}

menu::~menu(){

}

// Update game
void menu::update(){
  if( key[KEY_ENTER])
    set_next_state( STATE_GAME);
}

// Draw to screen
void menu::draw(){
  // Draw stuff
  draw_sprite( buffer, main_menu, 0, 0);
  draw_sprite( screen, buffer, 0, 0);
}
