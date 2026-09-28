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

#include "Controls.h"
#include "states/Game.h"
#include "states/Init.h"
#include "states/Intro.h"
#include "states/Menu.h"
#include "states/State.h"

// Main function*/
int main() {
  // Setup basic functionality
  asw::core::init(128, 128, 4);
  asw::core::print_info();
  controls::bind();

  // Register scenes
  asw::scene::SceneManager<States> app;
  app.register_scene<Init>(States::Init, app);
  app.register_scene<Intro>(States::Intro, app);
  app.register_scene<Menu>(States::Menu, app);
  app.register_scene<Game>(States::Game, app);
  app.set_next_scene(States::Init);

  // Start game
  app.start();

  asw::core::shutdown();

  return 0;
}
