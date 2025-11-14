/* File: window.h
 * Author: Brogan
 */
#pragma once

#include "game/renderer/shader.h"
#include <memory>
#include <vector>

class Game;
class GLFWwindow;
class Model;

enum Status { OK, WindowInitFailed, GLFWInitFailed, GLADInitFailed };

class Renderer {
  /* Methods */
public:
  Renderer();
  ~Renderer();

  GLFWwindow *getGLFWWindow() { return m_window; };
  Status getStatus() { return m_status; };
  bool windowOpen();
  void init();

private:
  void renderLoop();

  /* Member Varaibles */
public:
private:
  Status m_status = OK;
  GLFWwindow *m_window;
  std::vector<std::unique_ptr<Model>> models;

  friend Game;
};
