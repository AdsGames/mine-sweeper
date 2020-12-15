#include "Intro.h"

#include "utility/tools.h"

// Constructor
Intro::Intro()
    : img_intro(load_png_ex("images/intro.png")),
      img_title(load_png_ex("images/title.png")) {}

// Destructor
Intro::~Intro() {
  destroy_bitmap(img_intro);
  destroy_bitmap(img_title);
}

// Draw to screen
void Intro::draw() {
  bool skip = false;

  // A.D.S. Games Splash
  highcolor_fade_in(img_intro, 8);

  for (int i = 0; i < 100; i++) {
    if (keypressed() || mouse_b & 1) {
      skip = true;
      break;
    }

    rest(10);
  }

  // Minesweeper Splash
  if (!skip) {
    highcolor_fade_out(8);
    highcolor_fade_in(img_title, 8);

    for (int i = 0; i < 100; i++) {
      if (keypressed() || mouse_b & 1)
        break;

      rest(10);
    }
  }

  highcolor_fade_out(8);

  set_next_state(STATE_MENU);
}
