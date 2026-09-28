#include "./Game.h"

#include <asw/asw.h>
#include <functional>
#include <string>
#include <utility>

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

  // Buttons
  const auto screen_size = asw::display::get_logical_size();
  ui = std::make_unique<asw::ui::Root>();
  ui->set_size(screen_size.x, screen_size.y);

  // Image only buttons: the hover image also shows while focused, so hide the
  // theme focus ring
  ui->ctx.theme.btn_focus_ring = asw::Color{0, 0, 0, 0};

  const auto add_button = [this](const std::string& image,
                                 const std::string& hover_image,
                                 const asw::Vec2<float>& position,
                                 std::function<void()> on_click) {
    auto& button = ui->root.add_child<asw::ui::Button>();
    button.draw_background = false;
    button.set_texture(asw::assets::load_texture(image), true);
    button.texture_hover = asw::assets::load_texture(hover_image);
    button.transform.position = position;
    button.on_click = std::move(on_click);
  };

  add_button("assets/images/buttons/button_yes.png",
             "assets/images/buttons/button_yes_hover.png",
             asw::Vec2<float>(36, 73),
             [this]() { manager.set_next_scene(States::Game); });
  add_button("assets/images/buttons/button_no.png",
             "assets/images/buttons/button_no_hover.png",
             asw::Vec2<float>(68, 72),
             [this]() { manager.set_next_scene(States::Menu); });

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
  }

  // Win or lose
  else if (gameState == GameState::WIN || gameState == GameState::LOSE) {
    controls::update_ui(*ui);
  }

  if (asw::input::get_action_down(controls::UI_BACK)) {
    manager.set_next_scene(States::Menu);
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
