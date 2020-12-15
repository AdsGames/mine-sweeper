/*
 * Minesweeper
 * Allan Legemaate
 * 2012
 * Simple minesweeper game
 */

#include <allegro.h>
#include <time.h>
#include <string>

#include "utility/MouseListener.h"

#include "Game.h"
#include "Init.h"
#include "Intro.h"
#include "Menu.h"
#include "State.h"

// FPS System
using namespace std::chrono_literals;
using namespace std::chrono;
constexpr nanoseconds timestep(16ms);

int fps = 0;
int frames_done = 0;

// Current state object
State* currentState = nullptr;

// Close button handler
volatile int close_button_pressed = FALSE;
void close_button_handler(void) {
  close_button_pressed = TRUE;
}
END_OF_FUNCTION(close_button_handler)

// Change game screen
void change_state() {
  // If the state needs to be changed
  if (nextState != STATE_NULL) {
    // Delete the current state
    if (nextState != STATE_EXIT) {
      delete currentState;
    }

    // Change the state
    switch (nextState) {
      case STATE_INIT:
        currentState = new Init();
        break;

      case STATE_INTRO:
        currentState = new Intro();
        break;

      case STATE_MENU:
        currentState = new Menu();
        break;

      case STATE_GAME:
        currentState = new Game();
        break;

      default:
      case STATE_EXIT:
        close_button_pressed = true;
        break;
    }

    // Change the current state ID
    stateID = nextState;

    // NULL the next state ID
    nextState = STATE_NULL;
  }
}

// Sets up game
void setup() {
  // Initializing
  allegro_init();
  install_keyboard();
  install_mouse();
  install_timer();
  install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, ".");
  set_color_depth(32);

  // Close button
  LOCK_FUNCTION(close_button_handler);
  set_close_button_callback(close_button_handler);

  // Game state
  stateID = STATE_NULL;
  nextState = STATE_NULL;
}

// Update game
void update() {
  change_state();
  MouseListener::update();
  currentState->update();
}

// Draw game
void draw() {
  currentState->draw();
}

// main function of program
int main() {
  // Setup basic functionality
  setup();

  // Set the current state ID
  stateID = STATE_INIT;

  // Set the current game state object
  currentState = new Init();

  using clock = high_resolution_clock;
  nanoseconds lag(0ns);
  auto time_start = clock::now();

  while (!key[KEY_ESC] && !close_button_pressed) {
    auto delta_time = clock::now() - time_start;
    time_start = clock::now();
    lag += duration_cast<nanoseconds>(delta_time);

    while (lag >= timestep) {
      lag -= timestep;
      update();
    }

    draw();
    frames_done++;
  }

  return 0;
}
END_OF_MAIN()
