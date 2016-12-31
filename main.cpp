/*
 * Allegro Image Viewer
 * Allan Legemaate
 * 30/12/2016
 * Made because windows sucks
 */

// Libs
#include <allegro.h>
#include <alpng.h>
#include "state.h"
#include "init.h"

// Current state object
state *currentState = NULL;

<<<<<<< HEAD
// Delete game state and free state resources
void clean_up(){
  delete currentState;
=======
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

int get_height;
int get_width;

int width, height;

void ticker(){
  ticks++;
>>>>>>> origin/master
}

// Close button handler
volatile int close_button_pressed = FALSE;

void close_button_handler(void){
  close_button_pressed = TRUE;
}
END_OF_FUNCTION(close_button_handler)


// Change game screen
void change_state(){
  //If the state needs to be changed
  if( nextState != STATE_NULL ){
    //Delete the current state
    if( nextState != STATE_EXIT ){
        delete currentState;
    }

    //Change the state
    switch( nextState ){
      case STATE_INIT:
        currentState = new init();
        break;
    }

    //Change the current state ID
    stateID = nextState;

    //NULL the next state ID
    nextState = STATE_NULL;
  }
}

// Setup game
void setup(){
  // Load allegro library
  allegro_init();
  alpng_init();
  install_timer();
  install_keyboard();
  install_mouse();
  install_joystick(JOY_TYPE_AUTODETECT);
  install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,".");
  set_color_depth(32);

  // Close button
  LOCK_FUNCTION(close_button_handler);
  set_close_button_callback(close_button_handler);

  // Game state
  stateID = STATE_NULL;
  nextState = STATE_NULL;
}

// Start here
int main(){
  // Setup basic functionality
  setup();

<<<<<<< HEAD
  //Set the current state ID
  stateID = STATE_INIT;
=======
  // Initializing
  allegro_init();
  alpng_init();
  install_keyboard();
  install_mouse();
  install_timer();
  set_color_depth(32);
  get_desktop_resolution(&get_width,&get_height);
  set_gfx_mode( GFX_AUTODETECT, get_width,get_height,0, 0);
  install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,".");
  set_window_title("Minesweeper");
>>>>>>> origin/master

  //Set the current game state object
  currentState = new init();

  // Run loop
  while( !key[KEY_ESC]){
    currentState -> update();
    currentState -> draw();
  }

  //Clean up
  clean_up();

  // End
  return 0;
}
END_OF_MAIN();
