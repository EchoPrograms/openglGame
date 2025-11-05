/* File: window.h
 * Author: Brogan
 */
#pragma once

#include <GLFW/glfw3.h>

class Game;

enum Status { OK, WindowInitFailed, GLFWInitFailed };

class Renderer {
  /* Methods */
public:
  Renderer();
  ~Renderer();

  GLFWwindow *getGLFWWindow() { return m_window; };
  Status getStatus() { return m_status; };

private:
  void renderLoop();

  /* Member Varaibles */
public:
private:
  Status m_status = OK;
  GLFWwindow *m_window;

  friend Game;
};
