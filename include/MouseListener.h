/**
 * Mouse Listener
 * Allan Legemaate
 * Listens for mouse buttons JUST pressed or JUST released
 *   since the last tick
 * 02/01/2017
**/


#ifndef MOUSELISTENER_H
#define MOUSELISTENER_H

#include <allegro.h>

enum MOUSE_BUTTONS {
  MOUSE_LEFT = 1,
  MOUSE_RIGHT = 2,
  MOUSE_MIDDLE = 3,
  MAX_MOUSE_BUTTONS
};

class mouseListener {
  public:
    static void update();
    static bool buttonPressed[MAX_MOUSE_BUTTONS];
    static bool buttonReleased[MAX_MOUSE_BUTTONS];
    static bool lastTicksButton[MAX_MOUSE_BUTTONS];
    static unsigned int x;
    static unsigned int y;
};

#endif // MOUSELISTENER_H
