/* File: game.cpp
 * Author: Brogan
 */

#include "game/game.h"
#include "game/input.h"
#include "game/renderer/renderer.h"
#include "game/renderer/model.h"
#include <iostream>

Game::Game() {
  m_renderer = new Renderer(); // Handles glfw and opengl

  // Checks for errors thrown by the initialization of the window
  switch (m_renderer->getStatus()) {
  case GLFWInitFailed:
    std::cerr << "Failed to initialize GLFW\n";
    return;
  case GLADInitFailed:
    std::cerr << "Failed to initialize GLAD\n";
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
  m_renderer->init();
  
  // Create a simple test cube
  auto testModel = std::make_unique<Model>("res/models/monkey.fbx");
  testModel->setPosition(glm::vec3(0.0f, 0.0f, -5.0f));
  testModel->setRotation(glm::vec3(-45.0f, 45.0f, 0.0f));
  m_renderer->addModel(std::move(testModel));

  // The capturing loop of the program
  while (m_renderer->windowOpen()) {
    Update();
  }
}

void Game::Update() {

  m_renderer->renderLoop();
  return;
}

Game::~Game() {
  delete m_inputMangager;
  delete m_renderer;
}
