/* File: game.cpp
 * Author: Brogan
 */

#include "game/game.h"
#include "game/input.h"
#include "game/renderer/renderer.h"
#include <iostream>

Game::Game() {
  m_renderer = new Renderer();

  switch (m_renderer->getStatus()) {
  case GLFWInitFailed:
    std::cerr << "Failed to initialize GLFW\n";
    return;
  case WindowInitFailed:
    std::cerr << "Failed to create window\n";
    return;
  case OK:
    break;
  default:
    std::cout << "how...?\n";
    break;
  }

  m_inputMangager = new InputManager(m_renderer->getGLFWWindow());

  while (!glfwWindowShouldClose(m_renderer->getGLFWWindow()))
    Update();

  g_Eng 
}

void Game::Update() { m_renderer->renderLoop(); }

Game::~Game() {
  delete m_inputMangager;
  delete m_renderer;
}
