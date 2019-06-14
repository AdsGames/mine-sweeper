#include "mouseListener.h"
#include "globals.h"

bool mouseListener::buttonPressed[MAX_MOUSE_BUTTONS] = { false};
bool mouseListener::buttonReleased[MAX_MOUSE_BUTTONS] = { false};
bool mouseListener::lastTicksButton[MAX_MOUSE_BUTTONS] = { false};
unsigned int mouseListener::x = 0;
unsigned int mouseListener::y = 0;

// Check those buttons!
void mouseListener::update() {
  for (int i = 1; i < MAX_MOUSE_BUTTONS; i++) {
    // Clear old values
    buttonPressed[i] = false;
    buttonReleased[i] = false;

    // Pressed since last tick?
    if ((mouse_b & i) != false && lastTicksButton[i] == false)
      buttonPressed[i] = true;

    // Released since last tick?
    if ((mouse_b & i) == false && lastTicksButton[i] != false)
      buttonReleased[i] = true;

    // Button changed
    if (lastTicksButton[i] != (mouse_b & i))
      lastTicksButton[i] = (mouse_b & i);

    x = mouse_x * NATIVE_SCREEN_W / SCREEN_W;
    y = mouse_y * NATIVE_SCREEN_H / SCREEN_H;
  }
}
