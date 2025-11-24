/* File: renderer.cpp
 * Author: Brogan
 */

// clang-format off
#include "game/renderer/renderer.h"
#include "constants.h"
#include "game/renderer/shader.h"
#include "game/renderer/model.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
// clang-format on

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
  
  // Initialize view and projection matrices
  m_viewMatrix = glm::mat4(1.0f);
  m_projectionMatrix = glm::mat4(1.0f);
}

void framebufferSizeCallback(GLFWwindow *, int width, int height) {
  glViewport(0, 0, width, height);
}

void Renderer::init() {
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glfwSetFramebufferSizeCallback(getGLFWWindow(), framebufferSizeCallback);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  
  // Set up default view and projection matrices
  m_viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
  m_projectionMatrix = glm::perspective(glm::radians(45.0f),
                                        (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT,
                                        0.1f, 100.0f);
}

void Renderer::addModel(std::unique_ptr<Model> model) {
  models.push_back(std::move(model));
}

void Renderer::renderLoop() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  // Render all models
  for (auto &model : models) {
    Shader &shader = model->getShader();
    shader.use();
    
    // Set uniforms for this model
    glm::mat4 modelMatrix = model->getModelMatrix();
    shader.setMat4("u_Model", modelMatrix);
    shader.setMat4("u_View", m_viewMatrix);
    shader.setMat4("u_Projection", m_projectionMatrix);
    
    // Draw the model
    model->Draw();
  }
  
  glfwSwapBuffers(getGLFWWindow());
  glfwPollEvents();
}

bool Renderer::windowOpen() { return !glfwWindowShouldClose(m_window); }

Renderer::~Renderer() {
  glfwDestroyWindow(m_window);
  glfwTerminate();
}
