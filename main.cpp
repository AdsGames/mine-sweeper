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

// Delete game state and free state resources
void clean_up(){
  delete currentState;
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

  //Set the current state ID
  stateID = STATE_INIT;

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
