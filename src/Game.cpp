#include "Game.h"

#include <asw/util/KeyListener.h>
#include <asw/util/MouseListener.h>

#include "globals.h"
#include "utility/tools.h"

#include <asw/asw.h>

// Init game state
void Game::init() {
  menu_win = asw::load::texture("assets/images/menu_win.png");
  menu_lose = asw::load::texture("assets/images/menu_lose.png");
  explode = asw::load::sample("assets/sounds/explode.wav");
  beep = asw::load::sample("assets/sounds/timer.wav");
  field = Minefield();
  menu_yes = Button(36, 73);
  menu_no = Button(68, 72);
  game_time = Timer();
  last_beep_time = 0;
  game_state = GameStates::game;
  sound = true;

  // Buttons
  menu_yes.SetImages("assets/images/buttons/button_yes.png",
                     "assets/images/buttons/button_yes_hover.png");
  menu_yes.SetOnClick([this]() { setNextState(StateEngine::STATE_GAME); });

  menu_no.SetImages("assets/images/buttons/button_no.png",
                    "assets/images/buttons/button_no_hover.png");
  menu_no.SetOnClick([this]() { setNextState(StateEngine::STATE_MENU); });

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
       " Time:" + std::to_string(int(game_time.GetElapsedTime<seconds>()))));

  // Game
  if (game_state == GameStates::game) {
    // Plays stressing timer sound
    if (game_time.GetElapsedTime<seconds>() > last_beep_time && sound == true) {
      asw::sound::play(beep, 255, 122);  // , 500
      last_beep_time++;
    }

    // Revealing
    if (MouseListener::mouse_pressed & 1) {
      int type = field.reveal(MouseListener::x, MouseListener::y);

      // Start timer
      if (!game_time.IsRunning()) {
        game_time.Start();
      }

      // Lose and reveal map
      if (type == 9) {
        asw::sound::play(explode, 255, 122);  // , random(500, 1500)
        game_state = GameStates::lose;
        game_time.Stop();
      }
    }

    // Flagging
    else if (MouseListener::mouse_pressed & 4) {
      field.toggleFlag(MouseListener::x, MouseListener::y);
    }

    // Reveal Map
    if (field.getNumUnknown() == 0) {
      field.revealMap();
      game_state = GameStates::win;
      game_time.Stop();
    }
  }

  // Win or lose
  else if (game_state == GameStates::win || game_state == GameStates::lose) {
    menu_no.Update();
    menu_yes.Update();
  }

  if (KeyListener::keyPressed[SDL_SCANCODE_ESCAPE]) {
    setNextState(StateEngine::STATE_MENU);
  }
}

// All drawing goes on here
void Game::draw() {
  // Draw field
  field.draw();

  // Win and Lose menu text
  if (game_state == GameStates::win || game_state == GameStates::lose) {
    if (game_state == GameStates::win) {
      asw::draw::sprite(menu_win, 25, 42);
    } else if (game_state == GameStates::lose) {
      asw::draw::sprite(menu_lose, 25, 42);
    }

    // Buttons
    menu_yes.Draw();
    menu_no.Draw();
  }
}
