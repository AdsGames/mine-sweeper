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
  playing_board = create_bitmap( 640, 640);

  // Sets Sounds
  explode = load_sample( "sounds/explode.wav" );
  timer = load_sample( "sounds/timer.wav" );

  // Sets menu
  menu = load_bitmap( "images/menu.png", NULL);

  // Fonts
  FONT *f1, *f2, *f3, *f4, *f5;

  // Sets Font
  f1 = load_font( "data/arial_rounded_mt_bold.pcx", NULL, NULL);
  f2 = extract_font_range(f1, ' ', 'A'-1);
  f3 = extract_font_range(f1, 'A', 'Z');
  f4 = extract_font_range(f1, 'Z'+1, 'z');

  //  Merge fonts
  font = merge_fonts( f4, f5 = merge_fonts(f2, f3));

  //  Destroy temporary fonts
  destroy_font(f1);
  destroy_font(f2);
  destroy_font(f3);
  destroy_font(f4);
  destroy_font(f5);

  // Sets Variables
  mines = 0;
  flags = 0;

  width = 6;
  height = 5;

  mousedown = false;
  firstPress = false;
  sound = true;
  done = false;

  // Set to game
  gameScreen = 4;

  // Reset timer
  timeIn = 0;

  // Sets blocks
  for( int i = 0; i < width; i++){
    for( int t = 0; t < height; t++){
      // Mines
      if( random(0, 7) == 0){
        MyBlocks[i][t].SetType(9);
        mines++;
      }
      else{
        MyBlocks[i][t].SetType(0);
      }

      // Set info
      MyBlocks[i][t].SetImages( "images/blocks/none.png");
      MyBlocks[i][t].SetFlaged( false);
      MyBlocks[i][t].SetSelected( false);

      MyBlocks[i][t].SetWidth( playing_board -> w/width);
      MyBlocks[i][t].SetHeight( playing_board -> h/height);

      // Set position
      MyBlocks[i][t].SetX( i * ( playing_board -> w/width));
      MyBlocks[i][t].SetY( t * ( playing_board -> h/height));
    }
  }

  // Number based on surrounding mines
  for( int i = 0; i < width; i++){
    for( int t = 0; t < height; t++){
      if( MyBlocks[i][t].GetType() != 9){
        int type = 0;

        if( i < width){
          if( MyBlocks[i+1][t].GetType() == 9){ type++;}
        }
        if( i < width - 1 && t > 0){
          if( MyBlocks[i+1][t-1].GetType() == 9){ type++;}
        }
        if( i < width - 1 && t < height - 1){
          if( MyBlocks[i+1][t+1].GetType() == 9){ type++;}
        }
        if( t < height - 1){
          if( MyBlocks[i][t+1].GetType() == 9){ type++;}
        }
        if( i > 0){
          if( MyBlocks[i-1][t].GetType() == 9){ type++;}
        }
        if( i > 0 && t > 0){
          if( MyBlocks[i-1][t-1].GetType() == 9){ type++;}
        }
        if( i > 0 && t < height - 1){
          if( MyBlocks[i-1][t+1].GetType() == 9){ type++;}
        }
        if( t > 0){
          if( MyBlocks[i][t-1].GetType() == 9){type++;}
        }
        MyBlocks[i][t].SetType(type);
      }
    }
  }

  // Cursor
  select_mouse_cursor( MOUSE_CURSOR_ARROW);
  show_mouse( screen);
}

game::~game(){

}

// All game logic goes on here
void game::update(){
  // Game
  if( gameScreen == 4){
    // Plays stressing timer sound
    if( beepQueue && sound == true){
      play_sample(timer,255,122,500,0);
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
        gameScreen = 5;
        done = true;
      }
    }


    // Checks if mouse is in collision with object
    if( mouse_b){
      for( int i = 0; i < width; i++){
        for( int t = 0; t < height; t++){
          if( collisionAny( mouse_x, mouse_x, MyBlocks[i][t].GetX(), MyBlocks[i][t].GetX() + MyBlocks[i][t].GetWidth(), mouse_y, mouse_y, MyBlocks[i][t].GetY() + 80, MyBlocks[i][t].GetY() + 80 + MyBlocks[i][t].GetHeight())){
            if( mouse_b & 1 && mousedown == false && MyBlocks[i][t].GetFlaged() == false){
              MyBlocks[i][t].Change();
              MyBlocks[i][t].SetSelected(true);
              if( MyBlocks[i][t].GetType() == 9){
                play_sample(explode,255,122,random(500, 1500),0);
                // Reveal Map
                for( int i = 0; i < width; i++){
                  for( int t = 0; t < height; t++){
                    MyBlocks[i][t].Change();
                  }
                }
                gameScreen = 6;
                done = true;
              }
              mousedown=true;
            }
            if( mouse_b & 2 && mousedown == false){
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
              mousedown = true;
            }
          }
        }
      }
    }

    // Checks near blocks and removes wrapping
    for( int i = 0; i < width; i++){
      for( int t = 0; t < height; t++){
        if( MyBlocks[i][t].GetSelected() == true && MyBlocks[i][t].GetType() == 0){
          MyBlocks[i][t].SetType(10);
          MyBlocks[i][t].Change();
          if( i < width - 1){
            MyBlocks[i+1][t].Change();
            MyBlocks[i+1][t].SetSelected(true);
          }
          if( i < width - 1 && t > 0){
            MyBlocks[i+1][t-1].Change();
            MyBlocks[i+1][t-1].SetSelected(true);
          }
          if( i < width - 1 && t < height - 1){
            MyBlocks[i+1][t+1].Change();
            MyBlocks[i+1][t+1].SetSelected(true);
          }
          if( t < height - 1){
            MyBlocks[i][t+1].Change();
            MyBlocks[i][t+1].SetSelected(true);
          }
          if( i > 0){
            MyBlocks[i-1][t].Change();
            MyBlocks[i-1][t].SetSelected(true);
          }
          if( i > 0 && t > 0){
            MyBlocks[i-1][t-1].Change();
            MyBlocks[i-1][t-1].SetSelected(true);
          }
          if( i > 0 && t < height - 1){
            MyBlocks[i-1][t+1].Change();
            MyBlocks[i-1][t+1].SetSelected(true);
          }
          if( t > 0){
            MyBlocks[i][t-1].Change();
            MyBlocks[i][t-1].SetSelected(true);
          }
        }
      }
    }

    // Resets Mousdown
    if( !mouse_b && !key[KEY_SPACE]){
      mousedown = false;
    }
  }

  // Win or lose
  else if( gameScreen == 5 || gameScreen == 6){
    int newgame = 0;

    // Press buttons
    if( mouse_b & 1){
      if( collisionAny( mouse_x, mouse_x, 340, 520, mouse_y, mouse_y, 520, 580)){
        set_next_state( STATE_GAME);
        gameScreen = 4;
        highcolor_fade_out(8);
      }
      else if( collisionAny( mouse_x, mouse_x, 760, 940, mouse_y, mouse_y, 520, 580)){
        set_next_state( STATE_MENU);
      }
    }
  }
}


// All drawing goes on here
void game::draw(){
  // Draws background
  rectfill( buffer, 0, 0, SCREEN_W, SCREEN_H, makecol( 0, 0, 0));

  // Draw blocks
  for( int i = 0; i < width; i++){
    for( int t = 0; t < height; t++){
      MyBlocks[i][t].draw(playing_board, playing_board -> w/width, playing_board -> h/height);
    }
  }

  // Stretch tiles to fit
  stretch_sprite( buffer, playing_board, 0, 60, SCREEN_W, SCREEN_H - 60);

  // Game Text
  if( gameScreen == 4){
    textprintf_right_ex( buffer, font, 1240, 0, makecol(255,255,255), -1, "Mines Left: %i", mines-flags);
    textprintf_ex( buffer, font, 40, 0, makecol(255,255,255), -1, "Time: %i", timeIn);
  }
  // Win menu text
  else if( gameScreen == 5){
    textprintf_centre_ex( buffer,font,640,320, makecol(0,0,0),-1,"You Win!");
    textprintf_centre_ex( buffer,font,640,380, makecol(0,0,0),-1,"Time: %i Seconds",timeIn);
  }
  // Lose menu text
  else{
    textprintf_centre_ex( buffer,font,640,320, makecol(0,0,0),-1,"You Lose!");
    textprintf_centre_ex( buffer,font,640,380, makecol(0,0,0),-1,"Mines Left: %i",mines-flags);
  }

  // Draws buffer
  stretch_sprite( screen, buffer, 0, 0, SCREEN_W, SCREEN_H);
}
