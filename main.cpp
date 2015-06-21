#include <allegro.h>
#include <alpng.h>
#include <string>
#include <time.h>
#include "tools.h"

#include"block.h"

// Creates the blocks on screen
Block MyBlocks[100][100];

// Images
BITMAP* buffer;
BITMAP* cursor;
BITMAP* bimages[11];
BITMAP* foreground;
BITMAP* menu;
BITMAP* splash;
BITMAP* title;
BITMAP* playing_board;

// Sounds
SAMPLE* explode;
SAMPLE* timer;

// Fonts
FONT *f1, *f2, *f3, *f4, *f5;

// Variables
int done;
int mines;
int flags;
int gameScreen;

bool mousedown;
bool firstPress;
bool sound;
bool closeGame;

volatile bool beepQueue = false;
volatile int timeIn = 0;

// FPS System
volatile int ticks = 0;
int updates_per_second = 100;
volatile int game_time = 0;

int fps;
int frames_done;
int old_time;

int width, height;

void ticker(){
  ticks++;
}
END_OF_FUNCTION(ticker)

void game_time_ticker(){
  game_time++;
}
END_OF_FUNCTION(ticker)


void beeper(){
  if( !done){
    beepQueue = true;
    timeIn ++;
  }
}
END_OF_FUNCTION(ticker)

// Sets up game
void setup(bool first){
  if(first){
    // Creates a random number generator (based on time)
    srand( time(NULL));

    // Setup for FPS system
    LOCK_VARIABLE(ticks);
    LOCK_FUNCTION(ticker);
    install_int_ex( ticker, BPS_TO_TIMER(updates_per_second));

    LOCK_VARIABLE(game_time);
    LOCK_FUNCTION(game_time_ticker);
    install_int_ex( game_time_ticker, BPS_TO_TIMER(10));

    LOCK_VARIABLE(beepQueue);
    LOCK_FUNCTION(beeper);
    install_int_ex( beeper, BPS_TO_TIMER(1));

    // Set variables
    gameScreen = 0;

    // Sets Cursors
    cursor = load_bitmap( "images/cursor.png", NULL);

    // Creates a buffer
    buffer = create_bitmap( 640, 480);

    // Board for the tiles
    playing_board = create_bitmap( 640, 480);

    // Sets Starting Images
    title = load_bitmap( "images/title.png", NULL);
    splash = load_bitmap( "images/splash.png", NULL);

    // Sets Foreground
    foreground = load_bitmap( "images/foreground.png", NULL);

    // Sets Sounds
    explode = load_sample( "sounds/explode.wav" );
    timer = load_sample( "sounds/timer.wav" );

    // Sets menu
    menu = load_bitmap( "images/menu.png", NULL);

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
  }

  // Sets Variables
  mines = 0;
  flags = 0;

  width = 16;
  height = 12;

  mousedown = false;
  firstPress = false;
  sound = true;

  // Reset timer
  timeIn = 0;

  // Sets blocks
  for( int i = 0; i < width; i++){
    for( int t = 0; t < height; t++){
      // Back to 0
      MyBlocks[i][t].SetType(0);

      // Mines
      if( random(0, 7) == 0){
        MyBlocks[i][t].SetType(9);
        mines++;
      }

      // Number based on surrounding mines
      if( MyBlocks[i][t].GetType() != 9){
        int type = 0;

        if( i < width){
          if( MyBlocks[i+1][t].GetType() == 9){type++;}
        }
        if( i < width - 1 && t > 0){
          if( MyBlocks[i+1][t-1].GetType() == 9){type++;}
        }
        if( i < width - 1 && t < height - 1){
          if( MyBlocks[i+1][t+1].GetType() == 9){type++;}
        }
        if( t < height - 1){
          if( MyBlocks[i][t+1].GetType() == 9){type++;}
        }
        if( i > 0){
          if( MyBlocks[i-1][t].GetType() == 9){type++;}
        }
        if( i > 0 && t > 0){
          if( MyBlocks[i-1][t-1].GetType() == 9){type++;}
        }
        if( i > 0 && t < height - 1){
          if( MyBlocks[i-1][t+1].GetType() == 9){type++;}
        }
        if( t > 0){
          if( MyBlocks[i][t-1].GetType() == 9){type++;}
        }
        MyBlocks[i][t].SetType(type);
      }

      // Set info
      MyBlocks[i][t].SetImages("images/blocks/none.png");
      MyBlocks[i][t].SetFlaged(false);
      MyBlocks[i][t].SetSelected(false);

      MyBlocks[i][t].SetWidth( playing_board -> w/width);
      MyBlocks[i][t].SetHeight( playing_board -> h/height);

      // Set position
      MyBlocks[i][t].SetX(i * ( playing_board -> w/width));
      MyBlocks[i][t].SetY(t * ( playing_board -> h/height));
    }
  }
}

// Updates screen, does mouse routines and checks for falling
void game(){
  // A.D.S. Games Splash
  if( gameScreen == 0){
    highcolor_fade_in(splash,8);
    rest(2000);
    highcolor_fade_out(8);
    gameScreen = 1;
  }

  // Minesweeper Splash
  else if( gameScreen == 1){
    highcolor_fade_in(title,8);
    readkey();
    highcolor_fade_out(8);
    gameScreen = 4;
    setup(false);
  }

  // Menu
  else if( gameScreen == 2){
    gameScreen = 3;
  }

  // Difficulty Select
  else if( gameScreen == 3){
    gameScreen = 4;
  }

  // Game
  else if( gameScreen == 4){
    // Plays stressing timer sound
    if( beepQueue && sound==true){
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
      }
    }


    // Checks if mouse is in collision with object
    if( mouse_b){
      for( int i = 0; i < width; i++){
        for( int t = 0; t < height; t++){
          if( collisionAny( mouse_x, mouse_x, MyBlocks[i][t].GetX(), MyBlocks[i][t].GetX() + MyBlocks[i][t].GetWidth(), mouse_y, mouse_y, MyBlocks[i][t].GetY(), MyBlocks[i][t].GetY() + MyBlocks[i][t].GetHeight())){
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
    if(!mouse_b && !key[KEY_SPACE]){
      mousedown=false;
    }

    // Counter for FPS
    frames_done++;
  }

  // Win
  else if( gameScreen == 5){
    int newgame = 0;

    // Press buttons
    if( mouse_b & 1){
      if( mouse_x < 260 && mouse_x > 170 && mouse_y < 290 && mouse_y > 260){
        setup(false);
        gameScreen = 4;
        highcolor_fade_out(8);
      }
      else if( mouse_x < 470&&mouse_x > 380 && mouse_y < 290 && mouse_y > 260){
        closeGame = true;
      }
    }
  }

  // Lose
  else if( gameScreen == 6){
    int newgame = 0;

    // Press buttons
    if( mouse_b & 1){
      if( collisionAny( mouse_x, mouse_x, 170, 260, mouse_y, mouse_y, 260, 290)){
        setup(false);
        gameScreen = 4;
        highcolor_fade_out(8);
      }
      else if( collisionAny( mouse_x, mouse_x, 380, 470, mouse_y, mouse_y, 260, 290)){
        closeGame = true;
      }
    }
  }

  // End game
  if(key[KEY_ESC]){
    closeGame = true;
  }
}

void draw(){
  // A.D.S. Games Splash
  if( gameScreen == 0){ }

  // Minesweeper Splash
  else if( gameScreen == 1){ }

  // Menu
  else if( gameScreen == 2){ }

  // Difficulty Select
  else if( gameScreen == 3){ }

  // Game
  else if( gameScreen == 4){
    // Draws background
    rectfill( buffer, 0, 0, SCREEN_W, SCREEN_H, makecol( 0, 0, 0));

    // Draw blocks
    for( int i = 0; i < width; i++){
      for( int t = 0; t < height; t++){
        MyBlocks[i][t].draw(buffer, playing_board -> w/width, playing_board -> h/height);
      }
    }

    // Draws foreground
    //draw_sprite( buffer, foreground, 0, 0);

    // Draws text
    textprintf_right_ex( buffer, font, 620, 0, makecol(255,255,255), -1,"Mines Left: %i" , mines-flags);
    textprintf_ex( buffer, font, 20, 0, makecol(255,255,255),-1, "Time: %i" , timeIn);

    // Draws Mouse
    draw_sprite( buffer, cursor, mouse_x-10, mouse_y-10);
  }

  // Win
  else if(gameScreen == 5){
    rectfill( buffer, 0, 0, SCREEN_W, SCREEN_H, makecol( 0, 0, 0));
    for( int i = 0; i < width; i++){
      for( int t = 0; t < height; t++){
        MyBlocks[i][t].draw( buffer, playing_board -> w/width, playing_board -> h/height);
      }
    }
    for( int i = 0; i < width; i++){
      for( int t = 0; t < height; t++){
        if( MyBlocks[i][t].GetSelected() == true){
          MyBlocks[i][t].draw(buffer, playing_board -> w/width, playing_board -> h/height);
        }
      }
    }

    draw_sprite(buffer, menu, 150, 150);
    draw_sprite(buffer, foreground, 0, 0);

    textprintf_centre_ex(buffer,font,320,155, makecol(0,0,0),-1,"You Win!");
    textprintf_centre_ex(buffer,font,320,185, makecol(0,0,0),-1,"Time: %i Seconds",timeIn);

    draw_sprite( buffer, cursor, mouse_x, mouse_y);
  }

  // Lose
  else if(gameScreen == 6){
    rectfill( buffer, 0, 0, SCREEN_W, SCREEN_H, makecol( 0, 0, 0));
    for( int i = 0; i < width; i++){
      for( int t = 0; t < height; t++){
        MyBlocks[i][t].draw( buffer, playing_board -> w/width, playing_board -> h/height);
      }
    }
    for( int i = 0; i < width; i++){
      for( int t = 0; t < height; t++){
        if( MyBlocks[i][t].GetSelected() == true){
          MyBlocks[i][t].draw(buffer, playing_board -> w/width, playing_board -> h/height);
        }
      }
    }

    draw_sprite(buffer, menu, 150, 150);
    draw_sprite(buffer, foreground, 0, 0);

    textprintf_centre_ex(buffer,font,320,155, makecol(0,0,0),-1,"You Lose!");
    textprintf_centre_ex(buffer,font,320,185, makecol(0,0,0),-1,"Mines Left: %i",mines-flags);

    draw_sprite( buffer, cursor, mouse_x, mouse_y);
  }

  // Draws buffer
  stretch_sprite( screen, buffer, 0, 0, SCREEN_W, SCREEN_H);
}

// main function of program
int main(){

  // Initializing
  allegro_init();
  alpng_init();
  install_keyboard();
  install_mouse();
  install_timer();
  set_color_depth(32);
  set_gfx_mode( GFX_AUTODETECT_WINDOWED, 1280, 960, 0, 0);
  install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,".");
  set_window_title("Minesweeper");

  // Setup game
  setup(true);

  // Handles exit
  while(!closeGame){
    // Runs FPS system
    while(ticks == 0){
      rest(1);
    }
    while(ticks > 0){
      int old_ticks = ticks;
      // Update always
      game();
      ticks--;
      if(old_ticks <= ticks){
        break;
      }
    }
    if(game_time - old_time >= 10){
      fps = frames_done;
      frames_done = 0;
      old_time = game_time;
    }
    // Update every set amount of frames
    draw();
  }

  // Clears Memory
  delete [] buffer, cursor, bimages, foreground, title, explode, menu, font;

  allegro_exit();

  return 0;
}
END_OF_MAIN();
