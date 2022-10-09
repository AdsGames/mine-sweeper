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
    : nextState(ProgramState::STATE_NULL),
      currentState(ProgramState::STATE_NULL),
      state(nullptr) {}

// Draw
void StateEngine::draw() {
  if (state) {
    // Clear screen
    SDL_RenderClear(asw::display::renderer);

    state->draw();

    // Update screen
    SDL_RenderPresent(asw::display::renderer);
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
void StateEngine::setNextState(const ProgramState state) {
  nextState = state;
}

// Get state id
ProgramState StateEngine::getStateId() const {
  return currentState;
}

// Change game screen
void StateEngine::changeState() {
  // If the state needs to be changed
  if (nextState == ProgramState::STATE_NULL) {
    return;
  }

  // Delete the current state
  if (state) {
    state->cleanup();
    state = nullptr;
  }

  // Change the state
  switch (nextState) {
    case ProgramState::STATE_GAME:
      state = std::make_unique<Game>(*this);
      std::cout << ("Switched state to game.\n");
      break;

    case ProgramState::STATE_MENU:
      state = std::make_unique<Menu>(*this);
      std::cout << ("Switched state to main menu.\n");
      break;

    case ProgramState::STATE_INIT:
      state = std::make_unique<Init>(*this);
      std::cout << ("Switched state to init.\n");
      break;

    case ProgramState::STATE_INTRO:
      state = std::make_unique<Intro>(*this);
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
  nextState = ProgramState::STATE_NULL;
}

/*********
 * STATE
 *********/

// Change state
void State::setNextState(const ProgramState state) {
  this->engine.setNextState(state);
}
