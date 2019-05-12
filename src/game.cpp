#include "game.h"

// Timer for beep
void beeper(){
  if( !done){
    beepQueue = true;
    timeIn ++;
  }
}
END_OF_FUNCTION(ticker)

volatile bool beepQueue = false;
volatile int timeIn = 0;
int done;

// Init game state
game::game(){
  // Cursor
  enable_hardware_cursor();
  select_mouse_cursor(MOUSE_CURSOR_BUSY);
  show_mouse( screen);

  // Timer for beeping
  LOCK_VARIABLE(beepQueue);
  LOCK_FUNCTION(beeper);
  install_int_ex( beeper, BPS_TO_TIMER(1));

  // Creates a buffer
  buffer = create_bitmap( SCREEN_W, SCREEN_H);

  // Board for the tiles
  playing_board = create_bitmap( 640, 580);

  // Sets Sounds
  explode = load_sample( "sounds/explode.wav" );
  timer = load_sample( "sounds/timer.wav" );

  // Sets menu
  menu = load_png( "images/menu.png", NULL);

  // Buttons
  menu_yes.set_images( "images/buttons/button_yes.png", "images/buttons/button_yes_hover.png");
  menu_yes.set_position( 156, 398);
  menu_no.set_images( "images/buttons/button_no.png", "images/buttons/button_no_hover.png");
  menu_no.set_position( 368, 398);

  // Fonts
  FONT *f1, *f2, *f3, *f4, *f5;

  // Sets Font
  f1 = load_font( "data/arial_rounded_mt_bold.pcx", NULL, NULL);
  f2 = extract_font_range( f1, ' ', 'A'-1);
  f3 = extract_font_range( f1, 'A', 'Z');
  f4 = extract_font_range( f1, 'Z'+1, 'z');

  // Merge fonts
  font = merge_fonts( f4, f5 = merge_fonts(f2, f3));

  // Destroy temporary fonts
  destroy_font(f1);
  destroy_font(f2);
  destroy_font(f3);
  destroy_font(f4);
  destroy_font(f5);

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
  select_mouse_cursor( MOUSE_CURSOR_ARROW);
  show_mouse( screen);

  // Init blocks
  // Sets blocks
  for( int i = 0; i < width; i++){
    for( int t = 0; t < height; t++){
      // Set info
      MyBlocks[i][t].SetImages( "images/blocks/none.png");
      MyBlocks[i][t].SetWidth( playing_board -> w/width);
      MyBlocks[i][t].SetHeight( playing_board -> h/height);

      // Set position
      MyBlocks[i][t].SetX( i * ( playing_board -> w/width));
      MyBlocks[i][t].SetY( t * ( playing_board -> h/height));
    }
  }
}

// Clean up
game::~game(){
  // Fade out
  highcolor_fade_out(8);

  // Destroy bitmaps
  destroy_bitmap( buffer);
  destroy_bitmap( menu);
  destroy_bitmap( playing_board);

  // Destroy sounds
  destroy_sample( explode);
  destroy_sample( timer);
}

// Generate minefield
void game::generate_map( int x, int y){
  // Sets blocks
  for( int i = 0; i < width; i++){
    for( int t = 0; t < height; t++){
      // Mines
      if( random(0, 6) == 0 && !(i == x && t == y)){
        MyBlocks[i][t].SetType(9);
        mines++;
      }
      else{
        MyBlocks[i][t].SetType(0);
      }
    }
  }

  // Number based on surrounding mines
  for( int i = 0; i < width; i++){
    for( int t = 0; t < height; t++){
      if( MyBlocks[i][t].GetType() != 9){
        int type = 0;

        // Surrounding 8 cells
        for( int j = -1; j <= 1; j ++){
          for( int k = -1; k <= 1; k ++){
            if( ((j < 0 && i > 0) || (j > 0 && i < width - 1) || j == 0) && ((k < 0 && t > 0) || (k > 0 && t < height - 1) || k == 0)){
              if( MyBlocks[i + j][t + k].GetType() == 9)
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
void game::update(){
  // Game
  if( gameScreen == MINISTATE_GAME){
    // Plays stressing timer sound
    if( beepQueue && sound == true){
      play_sample( timer, 255, 122, 500, 0);
      beepQueue = false;
    }

    // Checks for win
    if( mines - flags == 0){
      int blocks = 0;
      bool blanks = false;
      for( int i = 0; i < width; i++){
        for( int t = 0; t < height; t++){
          if( MyBlocks[i][t].GetFlaged() == true && MyBlocks[i][t].GetType() == 9){
            blocks++;
          }
          if( MyBlocks[i][t].GetSelected() == false && MyBlocks[i][t].GetFlaged() == false && MyBlocks[i][t].GetType() != 9){
            blanks = true;
          }
        }
      }

      // Reveal Map
      if( blocks == mines && !blanks){
        for( int i = 0; i < width; i++){
          for( int t = 0; t < height; t++){
            MyBlocks[i][t].Change();
          }
        }
        gameScreen = MINISTATE_WIN;
        done = true;
      }
    }


    // Checks if mouse is in collision with object
    if( mouseListener::buttonPressed[1] || mouseListener::buttonPressed[2]){
      for( int i = 0; i < width; i++){
        for( int t = 0; t < height; t++){
          if( collisionAny( mouse_x, mouse_x, MyBlocks[i][t].GetX(), MyBlocks[i][t].GetX() + MyBlocks[i][t].GetWidth(), mouse_y, mouse_y, MyBlocks[i][t].GetY() + 60, MyBlocks[i][t].GetY() + 60 + MyBlocks[i][t].GetHeight())){
            if( mouseListener::buttonPressed[1] && MyBlocks[i][t].GetFlaged() == false){
              // Generate on first click
              if( !firstPress){
                generate_map( i, t);
                firstPress = true;
              }

              MyBlocks[i][t].Change();
              MyBlocks[i][t].SetSelected(true);
              if( MyBlocks[i][t].GetType() == 9){
                play_sample( explode, 255, 122, random(500, 1500), 0);
                // Reveal Map
                for( int i = 0; i < width; i++){
                  for( int t = 0; t < height; t++){
                    MyBlocks[i][t].Change();
                  }
                }
                gameScreen = MINISTATE_LOSE;
                done = true;
              }
            }
            if( mouseListener::buttonPressed[2]){
              if( MyBlocks[i][t].GetSelected() == false){
                if( MyBlocks[i][t].GetFlaged() == false){
                  MyBlocks[i][t].SetFlaged(true);
                  flags++;
                }
                else{
                  MyBlocks[i][t].SetFlaged(false);
                  flags--;
                }
              }
            }
          }
        }
      }
    }

    // Checks near blocks and removes wrapping
    for( int i = 0; i < width; i++){
      for( int t = 0; t < height; t++){
        if( MyBlocks[i][t].GetSelected() == true && MyBlocks[i][t].GetType() == 0){
          // Make it non updating
          MyBlocks[i][t].SetType(10);
          MyBlocks[i][t].Change();

          // Surrounding 8 cells
          for( int j = -1; j <= 1; j ++){
            for( int k = -1; k <= 1; k ++){
              if( ((j < 0 && i > 0) || (j > 0 && i < width - 1) || j == 0) && ((k < 0 && t > 0) || (k > 0 && t < height - 1) || k == 0)){
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
  else if( gameScreen == MINISTATE_WIN || gameScreen == MINISTATE_LOSE){
    int newgame = 0;

    // Press buttons
    if( mouseListener::buttonPressed[1]){
      if( menu_yes.get_hover()){
        set_next_state( STATE_GAME);
      }
      else if( menu_no.get_hover()){
        set_next_state( STATE_MENU);
      }
    }
  }
  if( key[KEY_SPACE])
    set_next_state( STATE_MENU);
}


// All drawing goes on here
void game::draw(){
  // Draws background
  clear_to_color( buffer, 0x000000);

  // Draw blocks
  for( int i = 0; i < width; i++){
    for( int t = 0; t < height; t++){
      MyBlocks[i][t].draw( playing_board);
    }
  }

  // Draw board
  draw_sprite( buffer, playing_board, 0, 60);

  // Game Text
  textprintf_right_ex( buffer, font, SCREEN_W - 10, 10, makecol(255,255,255), -1, "Mines Left: %i", mines-flags);
  textprintf_ex( buffer, font, 10, 10, makecol(255,255,255), -1, "Time: %i", timeIn);

  // Win and Lose menu text
  if( gameScreen == MINISTATE_WIN || gameScreen == MINISTATE_LOSE){
    draw_sprite( buffer, menu, 128, 234);
    // Unique elements
    if( gameScreen == MINISTATE_WIN){
      textprintf_centre_ex( buffer, font, SCREEN_W/2, 260, makecol(0,0,0), -1, "You Win!");
      textprintf_centre_ex( buffer, font, SCREEN_W/2, 300, makecol(0,0,0), -1, "Time: %i Seconds", timeIn);
    }
    else if( gameScreen == MINISTATE_LOSE){
      textprintf_centre_ex( buffer, font, SCREEN_W/2, 260, makecol(0,0,0), -1, "You Lose!");
      textprintf_centre_ex( buffer, font, SCREEN_W/2, 300, makecol(0,0,0), -1, "Mines Left: %i", mines - flags);
    }
    textprintf_centre_ex( buffer, font, SCREEN_W/2, 340, makecol(0,0,0), -1, "Play Again?");
    // Buttons
    menu_yes.draw( buffer);
    menu_no.draw( buffer);
  }

  // Draws buffer
  stretch_sprite( screen, buffer, 0, 0, SCREEN_W, SCREEN_H);
}
