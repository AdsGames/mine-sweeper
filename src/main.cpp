/*
 * Minesweeper
 * Allan Legemaate
 * 2012
 * Simple minesweeper game
 */
// Includes
#include <asw/asw.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "states/Game.h"
#include "states/Init.h"
#include "states/Intro.h"
#include "states/Menu.h"
#include "states/State.h"

// Main function*/
int main() {
  // Setup basic functionality
  asw::core::init(128, 128, 4);

  // Register scenes
  asw::scene::SceneManager<States> app;
  app.registerScene<Init>(States::Init, app);
  app.registerScene<Intro>(States::Intro, app);
  app.registerScene<Menu>(States::Menu, app);
  app.registerScene<Game>(States::Game, app);
  app.setNextScene(States::Init);

  // Start game
  app.start();

  return 0;
}
