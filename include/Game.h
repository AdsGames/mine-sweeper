/*
 * Game state
 * Allan Legemaate
 * 30/12/2016
 * Main program here
 */

#ifndef GAME_H
#define GAME_H

#include "State.h"

#include "utility/Timer.h"
#include "ui/Button.h"

#include "Minefield.h"

class Game : public State {
  public:
    // Construct/destruct
    Game();
    virtual ~Game();

    // Override parent
    virtual void update() override;
    virtual void draw() override;

  private:
    // Disallow copy
    Game (const Game &);
    Game &operator= (const Game &);

    // Bitmaps
    BITMAP *buffer, *menu_win, *menu_lose;

    // Sounds
    SAMPLE *explode, *beep;

    // Minefield
    Minefield field;

    // Buttons
    Button menu_yes, menu_no;

    // Game timer
    Timer game_time;
    int last_beep_time;

    // Mini state in game
    int game_state;
    enum game_states {
      game,
      win,
      lose
    };

    // Sound enabled
    bool sound;
};

#endif // GAME_H
