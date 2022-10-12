#include "Game.h"

#include <asw/util/KeyListener.h>
#include <asw/util/MouseListener.h>

#include "globals.h"
#include "utility/tools.h"

#include <asw/asw.h>

// Init game state
void Game::init() {
  menuWin = asw::load::texture("assets/images/menu_win.png");
  menuLose = asw::load::texture("assets/images/menu_lose.png");
  explode = asw::load::sample("assets/sounds/explode.wav");
  beep = asw::load::sample("assets/sounds/timer.wav");
  field = Minefield();
  menuYes = Button(36, 73);
  menuNo = Button(68, 72);
  gameTime = Timer();
  lastBeepTime = 0;
  gameState = GameState::GAME;
  sound = true;

  // Buttons
  menuYes.setImages("assets/images/buttons/button_yes.png",
                    "assets/images/buttons/button_yes_hover.png");
  menuYes.setOnClick([this]() { setNextState(ProgramState::STATE_GAME); });

  menuNo.setImages("assets/images/buttons/button_no.png",
                   "assets/images/buttons/button_no_hover.png");
  menuNo.setOnClick([this]() { setNextState(ProgramState::STATE_MENU); });

  // Create minefield
  switch (game_difficulty) {
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
void Game::update() {
  // Set title text
  asw::display::setTitle(
      (std::string("Mines Left: ") +
       std::to_string(field.getNumMines() - field.getNumFlagged()) +
       " Unknown Cells:" + std::to_string(field.getNumUnknown()) +
       " Time:" + std::to_string(int(gameTime.GetElapsedTime<seconds>()))));

  // Game
  if (gameState == GameState::GAME) {
    // Plays stressing timer sound
    if (gameTime.GetElapsedTime<seconds>() > lastBeepTime && sound == true) {
      asw::sound::play(beep, 127);  // , 500
      lastBeepTime++;
    }

    // Revealing
    if (MouseListener::mouse_pressed & 1) {
      int type = field.reveal(MouseListener::x, MouseListener::y);

      // Start timer
      if (!gameTime.IsRunning()) {
        gameTime.Start();
      }

      // Lose and reveal map
      if (type == 9) {
        asw::sound::play(explode, 255);  // , random(500, 1500)
        gameState = GameState::LOSE;
        gameTime.Stop();
      }
    }

    // Flagging
    else if (MouseListener::mouse_pressed & 4) {
      field.toggleFlag(MouseListener::x, MouseListener::y);
    }

    // Reveal Map
    if (field.getNumUnknown() == 0) {
      field.revealMap();
      gameState = GameState::WIN;
      gameTime.Stop();
    }
  }

  // Win or lose
  else if (gameState == GameState::WIN || gameState == GameState::LOSE) {
    menuNo.update();
    menuYes.update();
  }

  if (KeyListener::keyPressed[SDL_SCANCODE_ESCAPE]) {
    setNextState(ProgramState::STATE_MENU);
  }
}

// All drawing goes on here
void Game::draw() {
  // Draw field
  field.draw();

  // Win and Lose menu text
  if (gameState == GameState::WIN || gameState == GameState::LOSE) {
    if (gameState == GameState::WIN) {
      asw::draw::sprite(menuWin, 25, 42);
    } else if (gameState == GameState::LOSE) {
      asw::draw::sprite(menuLose, 25, 42);
    }

    // Buttons
    menuYes.draw();
    menuNo.draw();
  }
}
