/* File: renderer.cpp
 * Author: Brogan
 */

#include "game/renderer/renderer.h"
#include "constants.h"
#include "glad/glad.h"
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

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    m_status = GLADInitFailed;
    return;
  }
}

void Renderer::renderLoop() {

  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

  glfwSwapBuffers(getGLFWWindow());
}

bool Renderer::windowOpen() { return !glfwWindowShouldClose(m_window); }

Renderer::~Renderer() {
  glfwDestroyWindow(m_window);
  glfwTerminate();
}
