/* File: game.h
 * Author: Brogan
 */
#pragma once

#include "game/input.h"
#include "game/renderer/renderer.h"

class Game {
  /* Methods */
public:
  Game();
  ~Game();

private:
  void Update();

  /* member variables */
private:
  InputManager *m_inputMangager;
  Renderer *m_renderer;
  bool m_running;

public:
};
