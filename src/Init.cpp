#include "Init.h"

#include <allegro.h>
#include "globals.h"

// Defaults graphics mode
int Init::set_graphics(int max_scale) {
  while (max_scale > 0) {
    if (!set_gfx_mode(GFX_AUTODETECT_WINDOWED, max_scale * NATIVE_SCREEN_W,
                      max_scale * NATIVE_SCREEN_H, 0, 0))
      return max_scale;

    max_scale -= 1;
  }

  return 0;
}

// Construct state
Init::Init() {
  // Load config
  int count;
  push_config_state();
  set_config_file("config.ini");
  char** data = get_config_argv("graphics", "scale", &count);
  int scale = DEFAULT_SCALE;

  if (count == 1)
    scale = atoi(data[0]);

  pop_config_state();

  // Attempt to set screen mode from config
  scale = set_graphics(scale);

  if (!scale) {
    set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
    allegro_message("Could not create screen!");
    exit(EXIT_FAILURE);
  }

  // Run in background
  set_display_switch_mode(SWITCH_BACKGROUND);

  // Show mouse
  enable_hardware_cursor();
  select_mouse_cursor(MOUSE_CURSOR_ARROW);
  show_mouse(screen);

  // Title
  set_window_title("Minesweeper - A.D.S. Games");
}

// Update
void Init::update() {
  set_next_state(STATE_INTRO);
}
