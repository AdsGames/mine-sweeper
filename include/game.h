/*
 * Game state
 * Allan Legemaate
 * 30/12/2016
 * Main program here
 */
#ifndef GAME_H
#define GAME_H

#define MINISTATE_GAME 0
#define MINISTATE_WIN 1
#define MINISTATE_LOSE 2

#include "state.h"

#include "block.h"
#include "ui/Button.h"

extern void beeper();
extern volatile bool beepQueue;
extern volatile int timeIn;
extern int done;

class game : public state {
  public:
    // Construct/deconstruct
    game();
    virtual ~game();

    // Override parent
    virtual void update() override;
    virtual void draw() override;

  private:
    // Generate map
    void generate_map (int x, int y);

    // Reveal map
    void reveal_map();

    // Reveal at
    void reveal_at (int x, int y);

    // Creates the blocks on screen
    Block MyBlocks[16][16];

    // Images
    BITMAP *buffer;
    BITMAP *menu_win, *menu_lose;

    // Sounds
    SAMPLE *explode;
    SAMPLE *timer;

    // Buttons
    Button menu_yes, menu_no;

    // Variables
    int mines;
    int flags;
    int tiles_left;
    int game_state;

    bool firstPress;
    bool sound;

    int width, height;
};

#endif // GAME_H
