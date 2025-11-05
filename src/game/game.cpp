/* File: game.cpp
 * Author: Brogan
 */

#include "game/game.h"
#include "game/input.h"
#include "game/renderer/renderer.h"
#include <iostream>

Game::Game() {
  m_renderer = new Renderer(); // Handles glfw and opengl

  // Checks for errors thrown by the initialization of the window
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
    std::cout << "how...?\n"; // What have you done?
    break;
  }

  // The input manager uses GLFW to capture user input
  m_inputMangager = new InputManager(m_renderer->getGLFWWindow());
}

void Game::run() {
  // The capturing loop of the program
  while (m_renderer->windowOpen()) {
    Update();
  }
}

void Game::Update() {

  glfwPollEvents();
  m_renderer->renderLoop();
}

Game::~Game() {
  delete m_inputMangager;
  delete m_renderer;
}
