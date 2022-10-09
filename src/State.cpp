#include "State.h"

#include <iostream>

#include "Game.h"
#include "Init.h"
#include "Intro.h"
#include "Menu.h"

/*****************
 * STATE ENGINE
 *****************/

// Init
StateEngine::StateEngine()
    : nextState(StateEngine::STATE_NULL),
      currentState(StateEngine::STATE_NULL),
      state(nullptr) {}

// Draw
void StateEngine::draw() {
  if (state) {
    // Clear screen
    SDL_RenderClear(aar::display::renderer);

    state->draw();

    // Update screen
    SDL_RenderPresent(aar::display::renderer);
  }
}

// Update
void StateEngine::update() {
  if (state) {
    state->update();
  }

  changeState();
}

// Set next state
void StateEngine::setNextState(const int newState) {
  nextState = newState;
}

// Get state id
int StateEngine::getStateId() const {
  return currentState;
}

// Change game screen
void StateEngine::changeState() {
  // If the state needs to be changed
  if (nextState == STATE_NULL) {
    return;
  }

  // Delete the current state
  if (state) {
    state->cleanup();
    state = nullptr;
  }

  // Change the state
  switch (nextState) {
    case STATE_GAME:
      state = new Game(*this);
      std::cout << ("Switched state to game.\n");
      break;

    case STATE_MENU:
      state = new Menu(*this);
      std::cout << ("Switched state to main menu.\n");
      break;

    case STATE_INIT:
      state = new Init(*this);
      std::cout << ("Switched state to init.\n");
      break;

    case STATE_INTRO:
      state = new Intro(*this);
      std::cout << ("Switched state to intro.\n");
      break;

    default:
      std::cout << ("Exiting program.");
      break;
  }

  state->init();

  // Change the current state ID
  currentState = nextState;

  // NULL the next state ID
  nextState = STATE_NULL;
}

/*********
 * STATE
 *********/

// Change state
void State::setNextState(int state) {
  this->engine.setNextState(state);
}
