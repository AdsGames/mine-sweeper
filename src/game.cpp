#include "game.h"

#include <loadpng.h>

#include "tools.h"
#include "globals.h"
#include "mouseListener.h"

// Timer for beep
void beeper() {
  if (!done) {
    beepQueue = true;
    timeIn ++;
  }
}
END_OF_FUNCTION (ticker)

volatile bool beepQueue = false;
volatile int timeIn = 0;
int done;

// Init game state
game::game() {
  // Timer for beeping
  LOCK_VARIABLE (beepQueue);
  LOCK_FUNCTION (beeper);
  install_int_ex (beeper, BPS_TO_TIMER (1) );

  // Creates a buffer
  buffer = create_bitmap (128, 128);

  // Sets Sounds
  explode = load_sample ("sounds/explode.wav" );
  timer = load_sample ("sounds/timer.wav" );

  // Sets menu
  menu_win = load_png ("images/menu_win.png", nullptr);
  menu_lose = load_png ("images/menu_lose.png", nullptr);

  // Buttons
  menu_yes = Button (36, 73);
  menu_yes.setImages ("images/buttons/button_yes.png", "images/buttons/button_yes_hover.png");

  menu_no = Button (68, 72);
  menu_no.setImages ("images/buttons/button_no.png", "images/buttons/button_no_hover.png");


  width = game_difficulty;
  height = game_difficulty;

  mines = (width * height) / 4;
  tiles_left = (width * height) - mines;
  flags = 0;

  firstPress = false;
  done = false;
  sound = true;

  // Set to game
  game_state = MINISTATE_GAME;

  // Reset timer
  timeIn = 0;

  // Init blocks
  for (int i = 0; i < width; i++) {
    for (int t = 0; t < height; t++) {
      MyBlocks[i][t] = Block (i * (buffer -> w / width),
                              t * (buffer -> h / height),
                              buffer -> w / width,
                              buffer -> h / height);
    }
  }
}

// Clean up
game::~game() {
  // Fade out
  highcolor_fade_out (8);

  // Destroy bitmaps
  destroy_bitmap (buffer);
  destroy_bitmap (menu_win);
  destroy_bitmap (menu_lose);

  // Destroy sounds
  destroy_sample (explode);
  destroy_sample (timer);
}

// Generate minefield
void game::generate_map (int x, int y) {
  // Plant mines
  int mines_left = mines;

  while (mines_left > 0) {
    int random_x = random (0, width - 1);
    int random_y = random (0, height - 1);

    if (MyBlocks[random_x][random_y].GetType() != 9 &&
        random_x != x && random_y != y) {
      MyBlocks[random_x][random_y].SetType (9);
      mines_left --;
    }
  }

  // Number based on surrounding mines
  for (int i = 0; i < width; i++) {
    for (int t = 0; t < height; t++) {
      if (MyBlocks[i][t].GetType() != 9) {
        int type = 0;

        // Surrounding 8 cells
        for (int j = i - 1; j <= i + 1; j ++) {
          for (int k = t - 1; k <= t + 1; k ++) {
            if (j >= 0 && j < width &&
                k >= 0 && k < height) {
              type += MyBlocks[j][k].GetType() == 9;
            }
          }
        }

        MyBlocks[i][t].SetType (type);
      }
    }
  }
}

// Reveal some blocks recursively
void game::reveal_at (int x, int y) {
  if (x < 0 || x >= width ||
      y < 0 || y >= height ||
      MyBlocks[x][y].IsRevealed() ||
      MyBlocks[x][y].IsFlagged() )
    return;

  MyBlocks[x][y].Reveal();
  tiles_left--;

  if (MyBlocks[x][y].GetType() == 0) {
    for (int j = x - 1; j <= x + 1; j ++) {
      for (int k = y - 1; k <= y + 1; k ++) {
        if (! (j == x && k == y) )
          reveal_at (j, k);
      }
    }
  }
}

void game::reveal_map() {
  for (int i = 0; i < width; i++) {
    for (int t = 0; t < height; t++) {
      MyBlocks[i][t].Reveal();
    }
  }
}

// All game logic goes on here
void game::update() {
  // Set title text
  set_window_title ( (std::string ("Mines Left: ") + convertIntToString (mines - flags) + " Time:" + convertIntToString (timeIn) + " Tiles:" + convertIntToString (tiles_left) ).c_str() );

  // Game
  if (game_state == MINISTATE_GAME) {
    // Plays stressing timer sound
    if (beepQueue && sound == true) {
      play_sample (timer, 255, 122, 500, 0);
      beepQueue = false;
    }

    // Reveal Map
    if (tiles_left == 0) {
      reveal_map();
      game_state = MINISTATE_WIN;
      done = true;
    }

    // Checks if mouse is in collision with object
    if (mouseListener::buttonPressed[1] || mouseListener::buttonPressed[2]) {
      for (int i = 0; i < width; i++) {
        for (int t = 0; t < height; t++) {
          if (MyBlocks[i][t].MouseOver() ) {
            // Revealing
            if (mouseListener::buttonPressed[1] &&
                MyBlocks[i][t].IsFlagged() == false) {
              // Generate on first click
              if (!firstPress) {
                generate_map (i, t);
                firstPress = true;
              }

              // Reveal some blocks
              reveal_at (i, t);

              // Lose and reveal map
              if (MyBlocks[i][t].GetType() == 9) {
                play_sample (explode, 255, 122, random (500, 1500), 0);
                reveal_map();
                game_state = MINISTATE_LOSE;
                done = true;
              }
            }

            // Flagging
            else
              if (mouseListener::buttonPressed[2] &&
                  !MyBlocks[i][t].IsRevealed() ) {
                if (!MyBlocks[i][t].IsFlagged() ) {
                  MyBlocks[i][t].Flag();
                  flags++;
                }
                else {
                  MyBlocks[i][t].Unflag();
                  flags--;
                }
              }
          }
        }
      }
    }
  }

  // Win or lose
  else
    if (game_state == MINISTATE_WIN || game_state == MINISTATE_LOSE) {
      // Press buttons
      if (mouseListener::buttonPressed[1]) {
        if (menu_yes.hovering() ) {
          set_next_state (STATE_GAME);
        }
        else
          if (menu_no.hovering() ) {
            set_next_state (STATE_MENU);
          }
      }
    }

  if (key[KEY_Q])
    set_next_state (STATE_MENU);
}


// All drawing goes on here
void game::draw() {
  // Draws background
  clear_to_color (buffer, 0x000000);

  // Draw blocks
  for (int i = 0; i < width; i++) {
    for (int t = 0; t < height; t++) {
      MyBlocks[i][t].draw (buffer);
    }
  }

  // Win and Lose menu text
  if (game_state == MINISTATE_WIN || game_state == MINISTATE_LOSE) {
    if (game_state == MINISTATE_WIN)
      draw_sprite (buffer, menu_win, 25, 42);
    else
      if (game_state == MINISTATE_LOSE)
        draw_sprite (buffer, menu_lose, 25, 42);

    // Buttons
    menu_yes.draw (buffer);
    menu_no.draw (buffer);
  }

  // Draws buffer
  stretch_sprite (screen, buffer, 0, 0, SCREEN_W, SCREEN_H);
}
