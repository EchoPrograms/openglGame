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
  
  bool isRunning() { return m_running; }
  void run();
  void stop();

private:
  void Update();

  /* member variables */
private:
  InputManager *m_inputMangager;
  Renderer *m_renderer;
  bool m_running;

public:
};
