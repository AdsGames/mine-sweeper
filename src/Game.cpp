#include "Game.h"

#include "globals.h"
#include "utility/MouseListener.h"
#include "utility/tools.h"

// Init game state
Game::Game()
    : buffer(create_bitmap(128, 128)),
      menu_win(load_png_ex("images/menu_win.png")),
      menu_lose(load_png_ex("images/menu_lose.png")),
      explode(load_sample_ex("sounds/explode.wav")),
      beep(load_sample_ex("sounds/timer.wav")),
      field(Minefield()),
      menu_yes(Button(36, 73)),
      menu_no(Button(68, 72)),
      game_time(Timer()),
      last_beep_time(0),
      game_state(game_states::game),
      sound(true) {
  // Buttons
  menu_yes.SetImages("images/buttons/button_yes.png",
                     "images/buttons/button_yes_hover.png");
  menu_yes.SetOnClick([this]() { set_next_state(STATE_GAME); });

  menu_no.SetImages("images/buttons/button_no.png",
                    "images/buttons/button_no_hover.png");
  menu_no.SetOnClick([this]() { set_next_state(STATE_MENU); });

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

// Clean up
Game::~Game() {
  // Fade out
  highcolor_fade_out(8);

  // Destroy bitmaps
  destroy_bitmap(buffer);
  destroy_bitmap(menu_win);
  destroy_bitmap(menu_lose);

  // Destroy sounds
  destroy_sample(explode);
  destroy_sample(beep);
}

// All game logic goes on here
void Game::update() {
  // Set title text
  set_window_title(
      (std::string("Mines Left: ") +
       std::to_string(field.getNumMines() - field.getNumFlagged()) +
       " Unknown Cells:" + std::to_string(field.getNumUnknown()) +
       " Time:" + std::to_string(int(game_time.GetElapsedTime<seconds>())))
          .c_str());

  // Game
  if (game_state == game_states::game) {
    // Plays stressing timer sound
    if (game_time.GetElapsedTime<seconds>() > last_beep_time && sound == true) {
      play_sample(beep, 255, 122, 500, 0);
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
        play_sample(explode, 255, 122, random(500, 1500), 0);
        game_state = game_states::lose;
        game_time.Stop();
      }
    }

    // Flagging
    else if (MouseListener::mouse_pressed & 2) {
      field.toggleFlag(MouseListener::x, MouseListener::y);
    }

    // Reveal Map
    if (field.getNumUnknown() == 0) {
      field.revealMap();
      game_state = game_states::win;
      game_time.Stop();
    }
  }

  // Win or lose
  else if (game_state == game_states::win || game_state == game_states::lose) {
    menu_no.Update();
    menu_yes.Update();
  }

  if (key[KEY_ESC])
    set_next_state(STATE_MENU);
}

// All drawing goes on here
void Game::draw() {
  // Draws background
  clear_to_color(buffer, 0x000000);

  // Draw field
  field.draw(buffer);

  // Win and Lose menu text
  if (game_state == game_states::win || game_state == game_states::lose) {
    if (game_state == game_states::win)
      draw_sprite(buffer, menu_win, 25, 42);
    else if (game_state == game_states::lose)
      draw_sprite(buffer, menu_lose, 25, 42);

    // Buttons
    menu_yes.Draw(buffer);
    menu_no.Draw(buffer);
  }

  // Draws buffer
  stretch_sprite(screen, buffer, 0, 0, SCREEN_W, SCREEN_H);
}
