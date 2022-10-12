/*
 * Minesweeper
 * Allan Legemaate
 * 2012
 * Simple minesweeper game
 */
// Includes
#include <asw/asw.h>
#include <asw/util/KeyListener.h>
#include <asw/util/MouseListener.h>
#include <chrono>
#include <memory>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

// For state engine
#include "State.h"
#include "globals.h"

using namespace std::chrono_literals;
using namespace std::chrono;
constexpr nanoseconds timestep(16ms);

// State engine
std::unique_ptr<StateEngine> gameState;

// Functions
void setup();
void draw();
void update();

// FPS system
int fps = 0;
int frames_done = 0;

// Setup game
void setup() {
  gameState = std::make_unique<StateEngine>();
}

// Update
void update() {
  // Update listeners
  KeyListener::update();
  MouseListener::update();

  asw::core::update();

  // Do state logic
  gameState->update();

  // Handle exit
  if (gameState->getStateId() == ProgramState::STATE_EXIT) {
    asw::core::exit = true;
  }
}

// Do state rendering
void draw() {
  gameState->draw();
}

// Loop (emscripten compatibility)
#ifdef __EMSCRIPTEN__
void loop() {
  update();
  draw();
}
#endif

// Main function*/
int main(int argc, char* argv[]) {
  // Setup basic functionality
  setup();

  // Set the current state ID
  gameState->setNextState(ProgramState::STATE_INIT);

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(loop, 0, 1);
#else

  using clock = high_resolution_clock;
  nanoseconds lag(0ns);
  auto time_start = clock::now();

  while (!asw::core::exit) {
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
#endif

  return 0;
}
