#include "init.h"
#include "globals.h"

// Construct state
init::init() {
  // Set graphics mode
  scale = 4;
  if(set_gfx_mode(GFX_AUTODETECT_WINDOWED, 512, 512, 0, 0)) {
    scale = 2;
    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED, 256, 256, 0, 0)) {
      scale = 1;
      if(set_gfx_mode(GFX_AUTODETECT_WINDOWED, 128, 128, 0, 0)) {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        allegro_message("Could not create screen!");
        exit(EXIT_FAILURE);
      }
    }
  }

  // Title
  set_window_title("Minesweeper - A.D.S. Games");
}

// Update
void init::update(){
  set_next_state(STATE_INTRO);
}
