#include "state.h"

//State variables
int stateID;
int nextState;

// Set next state
void set_next_state(int newState) {
  if (nextState != STATE_EXIT) {
    nextState = newState;
  }
}
