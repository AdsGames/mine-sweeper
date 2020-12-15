/*
 * State for machine
 * Allan Legemaate
 * 30/12/2016
 * Compartmentalize program
 */
#ifndef STATE_H
#define STATE_H

// State variables
extern int stateID;
extern int nextState;

// Set next state
extern void set_next_state(int newState);

// Game states
enum programStates {
  STATE_NULL,
  STATE_INIT,
  STATE_INTRO,
  STATE_MENU,
  STATE_GAME,
  STATE_EXIT,
};

// State
class State {
 public:
  State(){};
  virtual ~State(){};

  // Draw to screen
  virtual void draw() = 0;

  // Update logic
  virtual void update() = 0;

 private:
  // Disallow copy
  State(const State&);
  State& operator=(const State&);
};

#endif  // STATE_H
