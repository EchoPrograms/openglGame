/* File: window.cpp
 * Author: Brogan
 */

#include "game/renderer/renderer.h"
#include "constants.h"
#include <GLFW/glfw3.h>

using namespace Constants::Renderer;

Renderer::Renderer() {
  if (!glfwInit()) {
    m_status = GLFWInitFailed;
    return;
  }

  m_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE,
                              nullptr, nullptr);
  if (!m_window) {
    glfwTerminate();
    m_status = WindowInitFailed;
    return;
  }

  glfwMakeContextCurrent(m_window);
}

void Renderer::renderLoop() {

  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

  glfwSwapBuffers(getGLFWWindow());
}

Renderer::~Renderer() {
  glfwDestroyWindow(m_window);
  glfwTerminate();
}
