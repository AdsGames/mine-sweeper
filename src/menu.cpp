#include "menu.h"

menu::menu(){
  // Creates a buffer
  buffer = create_bitmap( 640, 640);

  // Load menu background
  main_menu = load_bitmap( "images/main_menu.png", NULL);

  // Buttons
  start_easy.set_images( "images/buttons/start_easy.png", "images/buttons/start_easy_hover.png");
  start_easy.set_position( 166, 303);

  start_medium.set_images( "images/buttons/start_medium.png", "images/buttons/start_medium_hover.png");
  start_medium.set_position( 339, 303);

  start_hard.set_images( "images/buttons/start_hard.png", "images/buttons/start_hard_hover.png");
  start_hard.set_position( 166, 362);

  quit.set_images( "images/buttons/quit.png", "images/buttons/quit_hover.png");
  quit.set_position( 339, 362);

  // Cursor
  enable_hardware_cursor();
  select_mouse_cursor(MOUSE_CURSOR_ARROW);
  show_mouse( screen);
}

// Destructor
menu::~menu(){
  // Destroy bitmaps
  destroy_bitmap( main_menu);
  destroy_bitmap( buffer);
}

// Update game
void menu::update(){
  // Button presses
  if( mouse_b & 1){
    if( start_easy.get_hover()){
      game_difficulty = 8;
      set_next_state( STATE_GAME);
    }
    else if( start_medium.get_hover()){
      game_difficulty = 10;
      set_next_state( STATE_GAME);
    }
    else if( start_hard.get_hover()){
      game_difficulty = 14;
      set_next_state( STATE_GAME);
    }
    else if( quit.get_hover()){
      set_next_state( STATE_EXIT);
    }
  }
}

// Draw to screen
void menu::draw(){
  // Draw menu
  draw_sprite( buffer, main_menu, 0, 0);

  // Buttons
  start_easy.draw( buffer);
  start_medium.draw( buffer);
  start_hard.draw( buffer);
  quit.draw( buffer);

  // Buffer to screen
  draw_sprite( screen, buffer, 0, 0);
}
