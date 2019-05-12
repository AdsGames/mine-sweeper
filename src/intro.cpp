#include "intro.h"

// Constructor
intro::intro(){
  // Sets Starting Images
  img_title = load_png( "images/title.png", NULL);
  img_intro = load_png( "images/intro.png", NULL);
}

// Destructor
intro::~intro(){
  // Clean up images
  destroy_bitmap(img_intro);
  destroy_bitmap(img_title);
}

// Draw to screen
void intro::draw(){
  bool skip = false;

  // A.D.S. Games Splash
  highcolor_fade_in(img_intro, 8);
  for(int i = 0; i < 100; i++) {
    if (keypressed()) {
      skip = true;
      break;
    }
    rest(10);
  }

  // Minesweeper Splash
  if (!skip) {
    highcolor_fade_out(8);
    highcolor_fade_in(img_title, 8);
    for(int i = 0; i < 100; i++) {
      if (keypressed())
        break;
      rest(10);
    }
  }
  highcolor_fade_out(8);

  set_next_state( STATE_MENU);
}
