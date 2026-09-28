#include "./Game.h"

#include <asw/asw.h>
#include <memory>
#include <string>

#include "../Controls.h"
#include "../globals.h"

// Init game state
void Game::init() {
  menuWin = asw::assets::load_texture("assets/images/menu_win.png");
  menuLose = asw::assets::load_texture("assets/images/menu_lose.png");
  explode = asw::assets::load_sample("assets/sounds/explode.wav");
  beep = asw::assets::load_sample("assets/sounds/timer.wav");

  field = Minefield();

  gameTime = 0.0F;
  gameTimeRunning = false;
  lastBeepTime = 0;
  gameState = GameState::GAME;
  sound = true;

  // Play again buttons, image only: the hover image shows focus, so hide the
  // focus ring
  ui = std::make_unique<asw::ui::Root>();
  ui->ctx.navigation = controls::navigation();
  ui->ctx.theme.focus_ring.width = 0;
  ui->on_back = [this]() { manager.set_next_scene(States::Menu); };

  auto& yes = ui->root.add_child<asw::ui::Button>();
  yes.set_images(
      asw::assets::load_texture("assets/images/buttons/button_yes.png"),
      asw::assets::load_texture("assets/images/buttons/button_yes_hover.png"));
  yes.transform.position = asw::Vec2<float>(36, 73);
  yes.on_click = [this]() { manager.set_next_scene(States::Game); };

  auto& no = ui->root.add_child<asw::ui::Button>();
  no.set_images(
      asw::assets::load_texture("assets/images/buttons/button_no.png"),
      asw::assets::load_texture("assets/images/buttons/button_no_hover.png"));
  no.transform.position = asw::Vec2<float>(68, 72);
  no.on_click = [this]() { manager.set_next_scene(States::Menu); };

  // Create minefield
  switch (game_difficulty) {
    case 3:
      field = Minefield(20, 20, 80);
      break;

    case 2:
      field = Minefield(16, 16, 40);
      break;

    case 1:
      field = Minefield(12, 12, 19);
      break;

    default:
      field = Minefield(8, 8, 8);
      break;
  }
}

// All game logic goes on here
void Game::update(float dt) {
  field.update(dt);
  const auto mouse = asw::input::get_mouse();
  if (gameTimeRunning) {
    gameTime += dt;
  }

  // Set title text
  asw::display::set_title(
      (std::string("Mines Left: ") +
       std::to_string(field.getNumMines() - field.getNumFlagged()) +
       " Unknown Cells:" + std::to_string(field.getNumUnknown()) +
       " Time:" + std::to_string(int(gameTime))));

  // Game
  if (gameState == GameState::GAME) {
    // Plays stressing timer sound
    if (gameTime > lastBeepTime && sound) {
      asw::sound::play(beep, 0.5F, 0.0F);
      lastBeepTime++;
    }

    // Revealing
    if (asw::input::get_action_down(controls::REVEAL)) {
      const int type = field.reveal(mouse.position.x, mouse.position.y);

      // Start timer on the first reveal
      if (type != -1) {
        gameTimeRunning = true;
      }

      // Lose and reveal map
      if (type == 9) {
        asw::sound::play(explode, 1.0F, 0.0F);
        field.revealMap();
        gameState = GameState::LOSE;
        gameTimeRunning = false;
      }
    }

    // Flagging
    else if (asw::input::get_action_down(controls::FLAG)) {
      field.toggleFlag(mouse.position.x, mouse.position.y);
    }

    // Win once every safe cell is revealed
    if (gameState == GameState::GAME && field.isCleared()) {
      field.revealMap();
      gameState = GameState::WIN;
      gameTimeRunning = false;
    }

    if (asw::input::get_action_down(controls::UI_BACK)) {
      manager.set_next_scene(States::Menu);
    }
  }

  // Win or lose: only the play again buttons take input, so a click on them
  // never reaches the minefield. Back goes to the menu through ui->on_back.
  else {
    ui->update();
  }
}

// All drawing goes on here
void Game::draw() {
  // Draw field
  field.draw();

  // Win and Lose menu text
  if (gameState == GameState::WIN || gameState == GameState::LOSE) {
    if (gameState == GameState::WIN) {
      asw::draw::sprite(menuWin, {25, 42});
    } else if (gameState == GameState::LOSE) {
      asw::draw::sprite(menuLose, {25, 42});
    }

    // Buttons
    ui->draw();
  }
}
