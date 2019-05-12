#include "game.h"

#include "tools.h"
#include "globals.h"

// Timer for beep
void beeper() {
  if(!done) {
    beepQueue = true;
    timeIn ++;
  }
}
END_OF_FUNCTION(ticker)

volatile bool beepQueue = false;
volatile int timeIn = 0;
int done;

// Init game state
game::game() {
  // Cursor
  enable_hardware_cursor();
  select_mouse_cursor(MOUSE_CURSOR_BUSY);
  show_mouse(screen);

  // Timer for beeping
  LOCK_VARIABLE(beepQueue);
  LOCK_FUNCTION(beeper);
  install_int_ex(beeper, BPS_TO_TIMER(1));

  // Creates a buffer
  buffer = create_bitmap(128, 128);

  // Sets Sounds
  explode = load_sample("sounds/explode.wav" );
  timer = load_sample("sounds/timer.wav" );

  // Sets menu
  menu_win = load_png("images/menu_win.png", NULL);
  menu_lose = load_png("images/menu_lose.png", NULL);

  // Buttons
  menu_yes.set_images("images/buttons/button_yes.png", "images/buttons/button_yes_hover.png");
  menu_yes.set_position(36, 76);
  menu_no.set_images("images/buttons/button_no.png", "images/buttons/button_no_hover.png");
  menu_no.set_position(68, 76);

  // Sets Variables
  mines = 0;
  flags = 0;

  width = game_difficulty;
  height = game_difficulty;

  firstPress = false;
  sound = true;
  done = false;

  // Set to game
  gameScreen = MINISTATE_GAME;

  // Reset timer
  timeIn = 0;

  // Cursor
  select_mouse_cursor(MOUSE_CURSOR_ARROW);
  show_mouse(screen);

  // Init blocks
  // Sets blocks
  for(int i = 0; i < width; i++) {
    for(int t = 0; t < height; t++) {
      // Set info
      MyBlocks[i][t].SetImages("images/blocks/none.png");
      MyBlocks[i][t].SetWidth(buffer -> w/width);
      MyBlocks[i][t].SetHeight(buffer -> h/height);

      // Set position
      MyBlocks[i][t].SetX(i * (buffer -> w/width));
      MyBlocks[i][t].SetY(t * (buffer -> h/height));
    }
  }
}

// Clean up
game::~game() {
  // Fade out
  highcolor_fade_out(8);

  // Destroy bitmaps
  destroy_bitmap(buffer);
  destroy_bitmap(menu_win);
  destroy_bitmap(menu_lose);

  // Destroy sounds
  destroy_sample(explode);
  destroy_sample(timer);
}

// Generate minefield
void game::generate_map(int x, int y) {
  // Sets blocks
  for(int i = 0; i < width; i++) {
    for(int t = 0; t < height; t++) {
      // Mines
      if(random(0, 6) == 0 && !(i == x && t == y)) {
        MyBlocks[i][t].SetType(9);
        mines++;
      }
      else {
        MyBlocks[i][t].SetType(0);
      }
    }
  }

  // Number based on surrounding mines
  for(int i = 0; i < width; i++) {
    for(int t = 0; t < height; t++) {
      if(MyBlocks[i][t].GetType() != 9) {
        int type = 0;

        // Surrounding 8 cells
        for(int j = -1; j <= 1; j ++) {
          for(int k = -1; k <= 1; k ++) {
            if(((j < 0 && i > 0) || (j > 0 && i < width - 1) || j == 0) && ((k < 0 && t > 0) || (k > 0 && t < height - 1) || k == 0)) {
              if(MyBlocks[i + j][t + k].GetType() == 9)
                type ++;
            }
          }
        }
        MyBlocks[i][t].SetType(type);
      }
    }
  }
}

// All game logic goes on here
void game::update() {
  // Set title text
  set_window_title((std::string("Mines Left: ") + convertIntToString(mines-flags) + " Time:" + convertIntToString(timeIn)).c_str());

  // Game
  if(gameScreen == MINISTATE_GAME) {
    // Plays stressing timer sound
    if(beepQueue && sound == true) {
      play_sample(timer, 255, 122, 500, 0);
      beepQueue = false;
    }

    // Checks for win
    if(mines - flags == 0) {
      int blocks = 0;
      bool blanks = false;
      for(int i = 0; i < width; i++) {
        for(int t = 0; t < height; t++) {
          if(MyBlocks[i][t].GetFlagged() == true && MyBlocks[i][t].GetType() == 9) {
            blocks++;
          }
          if(MyBlocks[i][t].GetSelected() == false && MyBlocks[i][t].GetFlagged() == false && MyBlocks[i][t].GetType() != 9) {
            blanks = true;
          }
        }
      }

      // Reveal Map
      if(blocks == mines && !blanks) {
        for(int i = 0; i < width; i++) {
          for(int t = 0; t < height; t++) {
            MyBlocks[i][t].Change();
          }
        }
        gameScreen = MINISTATE_WIN;
        done = true;
      }
    }


    // Checks if mouse is in collision with object
    if(mouseListener::buttonPressed[1] || mouseListener::buttonPressed[2]) {
      for(int i = 0; i < width; i++) {
        for(int t = 0; t < height; t++) {
          if(collisionAny(mouse_x / scale, mouse_x / scale,
                          MyBlocks[i][t].GetX(), MyBlocks[i][t].GetX() + MyBlocks[i][t].GetWidth(),
                          mouse_y / scale, mouse_y / scale,
                          MyBlocks[i][t].GetY(), MyBlocks[i][t].GetY() + MyBlocks[i][t].GetHeight())){
            if(mouseListener::buttonPressed[1] && MyBlocks[i][t].GetFlagged() == false){
              // Generate on first click
              if(!firstPress){
                generate_map( i, t);
                firstPress = true;
              }

              MyBlocks[i][t].Change();
              MyBlocks[i][t].SetSelected(true);
              if( MyBlocks[i][t].GetType() == 9) {
                play_sample( explode, 255, 122, random(500, 1500), 0);
                // Reveal Map
                for(int i = 0; i < width; i++) {
                  for(int t = 0; t < height; t++) {
                    MyBlocks[i][t].Change();
                  }
                }
                gameScreen = MINISTATE_LOSE;
                done = true;
              }
            }
            if(mouseListener::buttonPressed[2]) {
              if(MyBlocks[i][t].GetSelected() == false) {
                if(MyBlocks[i][t].GetFlagged() == false) {
                  MyBlocks[i][t].SetFlagged(true);
                  flags++;
                }
                else {
                  MyBlocks[i][t].SetFlagged(false);
                  flags--;
                }
              }
            }
          }
        }
      }
    }

    // Checks near blocks and removes wrapping
    for(int i = 0; i < width; i++) {
      for(int t = 0; t < height; t++) {
        if(MyBlocks[i][t].GetSelected() == true && MyBlocks[i][t].GetType() == 0) {
          // Make it non updating
          MyBlocks[i][t].SetType(10);
          MyBlocks[i][t].Change();

          // Surrounding 8 cells
          for(int j = -1; j <= 1; j ++) {
            for(int k = -1; k <= 1; k ++) {
              if(((j < 0 && i > 0) || (j > 0 && i < width - 1) || j == 0) && ((k < 0 && t > 0) || (k > 0 && t < height - 1) || k == 0)) {
                MyBlocks[i + j][t + k].Change();
                MyBlocks[i + j][t + k].SetSelected(true);
              }
            }
          }
        }
      }
    }
  }

  // Win or lose
  else if(gameScreen == MINISTATE_WIN || gameScreen == MINISTATE_LOSE) {
    int newgame = 0;

    // Press buttons
    if(mouseListener::buttonPressed[1]) {
      if(menu_yes.get_hover()) {
        set_next_state(STATE_GAME);
      }
      else if(menu_no.get_hover()) {
        set_next_state(STATE_MENU);
      }
    }
  }
  if(key[KEY_SPACE])
    set_next_state(STATE_MENU);
}


// All drawing goes on here
void game::draw() {
  // Draws background
  clear_to_color(buffer, 0x000000);

  // Draw blocks
  for(int i = 0; i < width; i++) {
    for(int t = 0; t < height; t++) {
      MyBlocks[i][t].draw(buffer);
    }
  }

  // Win and Lose menu text
  if(gameScreen == MINISTATE_WIN || gameScreen == MINISTATE_LOSE) {
    if(gameScreen == MINISTATE_WIN)
      draw_sprite(buffer, menu_win, 25, 47);
    else if(gameScreen == MINISTATE_LOSE)
      draw_sprite(buffer, menu_lose, 25, 47);

    // Buttons
    menu_yes.draw(buffer);
    menu_no.draw(buffer);
  }

  // Draws buffer
  stretch_sprite(screen, buffer, 0, 0, SCREEN_W, SCREEN_H);
}
