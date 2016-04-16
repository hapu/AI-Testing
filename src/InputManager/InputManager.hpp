#pragma once
#ifndef _INPUTMANAGER_INPUTMANAGER_H_
#define _INPUTMANAGER_INPUTMANAGER_H_

#include <SDL2/SDL.h>

class InputManager {
 public:
  struct t_keyboard {
    bool space;
    bool lctrl;
    bool rctrl;
    bool lshift;
    bool rshift;
    bool up;
    bool down;
    bool left;
    bool right;
    bool w;
    bool a;
    bool s;
    bool d;
  };

  static t_keyboard keyboard;
  static void KeyDown(SDL_Keycode key);
  static void KeyUp(SDL_Keycode key);
};

#endif // _INPUTMANAGER_INPUTMANAGER_H_
