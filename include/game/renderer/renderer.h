/* File: window.h
 * Author: Brogan
 */
#pragma once

class Game;
class GLFWwindow;

enum Status { OK, WindowInitFailed, GLFWInitFailed, GLADInitFailed };

class Renderer {
  /* Methods */
public:
  Renderer();
  ~Renderer();

  GLFWwindow *getGLFWWindow() { return m_window; };
  Status getStatus() { return m_status; };
  bool windowOpen();
  void renderLoop();

  /* Member Varaibles */
public:
private:
  Status m_status = OK;
  GLFWwindow *m_window;

  friend Game;
};
