/*
 * Game state
 * Allan Legemaate
 * 30/12/2016
 * Main program here
 */
#ifndef GAME_H
#define GAME_H

#include "state.h"
#include "tools.h"
#include "block.h"

extern void beeper();
extern volatile bool beepQueue;
extern volatile int timeIn;
extern int done;

class game : public state{
  public:
    // Construct/deconstruct
    game();
    ~game();

    // Override parent
    void update();
    void draw();

  protected:

  private:
    // Creates the blocks on screen
    Block MyBlocks[100][100];

    // Images
    BITMAP* buffer;
    BITMAP* menu;
    BITMAP* playing_board;

    // Sounds
    SAMPLE* explode;
    SAMPLE* timer;

    // Variables
    int mines;
    int flags;
    int gameScreen;

    bool mousedown;
    bool firstPress;
    bool sound;

    int width, height;
};

#endif // GAME_H
